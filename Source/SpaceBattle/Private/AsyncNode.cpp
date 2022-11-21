// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncNode.h"

UAsyncNode* UAsyncNode::AsyncFerox(const int id) {
	UAsyncNode* NewFeroxNode = NewObject<UAsyncNode>();
	NewFeroxNode->temp = id;
	return NewFeroxNode;
}

void UAsyncNode::Activate() 
{
	isEqual();
}

void UAsyncNode::isEqual() 
{
	if (temp)
	{
		OnSuccess.Broadcast(temp, "Success from C++");
	}
	else 
	{
		OnFail.Broadcast(-228, "Fail");
	}
	RemoveFromRoot();
}