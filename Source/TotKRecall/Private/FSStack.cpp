#pragma once
#include "FSStack.h"

FSStack::FSStack() : mStackMax(40),
	mStack(MakeUnique<TArray<FVector>>())
{
	mStack->Reserve(mStackMax);
}

FSStack::FSStack(FSStack&& other) noexcept : mStackMax(other.mStackMax),
	mStack(MoveTemp(other.mStack))
{
}

FSStack::FSStack(const FSStack& other) : mStackMax(other.mStackMax),
	mStack(MakeUnique<TArray<FVector>>(*other.mStack))
{
}

FSStack::~FSStack()
{
}

bool FSStack::Pop(FVector& OutElem) const
{
	if (mStack->Num() > 0)
	{
		OutElem = mStack->Pop();
		return true;
	}
	
	return false;
}

bool FSStack::IsEmpty() const
{
	return mStack->Num() == 0;	
}

uint16_t FSStack::Num() const
{
	return mStack->Num();
}

void FSStack::Push(const FVector& Elem) const
{
	mStack->Add(Elem);

	if (mStack->Num() > mStackMax)
		mStack->RemoveAt(0);
}
