// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * A Custom Type that will act as a stack, that when exceeding its max wont expand, but will pop the first element out.
 */
class TOTKRECALL_API FSStack
{
public:
	//Default Constructor
	FSStack();
	//Move Constructor
	FSStack(FSStack&& other) noexcept;
	//Deep Copy Constructor
	FSStack(const FSStack& other);
	//Destructor
	~FSStack();

	//Add element to stack, and remove the first if overflowing
	void Push(const FVector& Elem) const;
	//Pop top element off stack
	bool Pop(FVector& OutElem) const;
	//Return is stack is empty
	bool IsEmpty() const;
	//Return the number of elements in the stack
	uint16_t Num() const;

private:
	//The max number of elements allowed in the stack
	uint16_t mStackMax;
	//The stack
	TUniquePtr<TArray<FVector>> mStack;
};