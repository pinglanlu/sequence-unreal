#pragma once


enum ErrorType
{
	NotFound,
	ResponseParseError,
	EmptyResponse,
	UnsupportedMethodOnChain,
	RequestFail,
	RequestTimeExceeded,
	TestFail,
};

class SequenceError
{
public:
	SequenceError(ErrorType Type, FString Message);
	FString Message;
	ErrorType Type;
};

template<typename T> using TResult = TValueOrError<T, SequenceError>;
