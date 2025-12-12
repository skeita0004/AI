#include "DeltaTime.h"
#include <Windows.h>

namespace {
	LARGE_INTEGER freq;
	LARGE_INTEGER current;
	float deltaTime;
};
void DeltaTime::Init()
{
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&current);
}

void DeltaTime::Refresh()
{
	LARGE_INTEGER last = current;
	QueryPerformanceCounter(&current);
	deltaTime = static_cast<float >(current.QuadPart - last.QuadPart) / freq.QuadPart;
}

float DeltaTime::GetDeltaTime()
{
	return deltaTime;
}
