/*
 * MIT License
 *
 * Copyright (c) 2023 Benoit Pelletier
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "DoorType.h"
#include "ProceduralDungeonUtils.h"

UDoorType::UDoorType()
	: UDataAsset()
{
	Size = Dungeon::DefaultDoorSize();
#if WITH_EDITOR
	Description = FText::FromString(TEXT("No Description"));
#endif
	bCompatibleWithItself = true;
}

FVector UDoorType::GetSize(const UDoorType* DoorType)
{
	return IsValid(DoorType) ? DoorType->Size : Dungeon::DefaultDoorSize();
}

bool UDoorType::AreCompatible(const UDoorType* A, const UDoorType* B)
{
	// If both are null, they are compatible
	if (!IsValid(A) && !IsValid(B))
		return true;

	// If only one of them is null, they are not compatible
	if (!IsValid(A) || !IsValid(B))
		return false;

	if (A == B)
		return A->bCompatibleWithItself;
	return A->Compatibility.Contains(B) || B->Compatibility.Contains(A);
}
