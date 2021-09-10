#include "SortEngine.hpp"
using namespace Sort;
//Global Variables  
int SleepTime = 500;
std::queue<std::vector<int>> InputQueue1, InputQueue2, InputQueue3;
std::mutex InputQueueMutex;

//Functions Prototype
void Observer();
void GenerateRandomVector();
bool isQueueTooLong(int inputvector, int min_size);
void PRINT_ALL_SIZE(int sleeptime, int BubbleSortsize, int QuickSortSize, int SelectionSortSize);

SortEngine* SortEngine::obj;

int main()
{
	std::thread VectorCreaterThread(GenerateRandomVector);
	std::thread Observer_Thread(Observer);
	/*
	Sort::SortEngine SortEngineObject1 = Sort::SortEngine(InputQueue1, Sort::BUBBLE,InputQueueMutex);
	Sort::SortEngine SortEngineObject2 = Sort::SortEngine(InputQueue2, Sort::QUICK, InputQueueMutex);
	Sort::SortEngine SortEngineObject3 = Sort::SortEngine(InputQueue3, Sort::SELECTION, InputQueueMutex);
	*/

	SortEngine* SortEngineObject1 = SortEngine::getInstance(InputQueue1, Sort::BUBBLE, InputQueueMutex);
	SortEngine* SortEngineObject2 = SortEngine::getInstance(InputQueue2, Sort::QUICK, InputQueueMutex);
	SortEngine* SortEngineObject3 = SortEngine::getInstance(InputQueue3, Sort::SELECTION, InputQueueMutex);


	std::thread SortEngineObject1_Thread(&Sort::SortEngine::Process, SortEngineObject1);
	std::thread SortEngineObject2_Thread(&Sort::SortEngine::Process, SortEngineObject2);
	std::thread SortEngineObject3_Thread(&Sort::SortEngine::Process, SortEngineObject3);

	VectorCreaterThread.join();
	Observer_Thread.join();

}



void Observer()
{
	while (true)
	{
		int InputQueueSize1, InputQueueSize2, InputQueueSize3;
		InputQueueMutex.lock();

		InputQueueSize1 = InputQueue1.size();
		InputQueueSize2 = InputQueue2.size();
		InputQueueSize3 = InputQueue3.size();

		InputQueueMutex.unlock();

		bool SpeedUp = true;

		int MIN_QUEUE_SIZE = 1;
		if (isQueueTooLong(InputQueueSize1, MIN_QUEUE_SIZE))
			SpeedUp = false;
		if (isQueueTooLong(InputQueueSize2, MIN_QUEUE_SIZE))
			SpeedUp = false;
		if (isQueueTooLong(InputQueueSize3, MIN_QUEUE_SIZE))
			SpeedUp = false;


		if (SpeedUp) {
			if (SleepTime >= 60) 	SleepTime = SleepTime - 50;
			else if (SleepTime < 60 && SleepTime>0) 	SleepTime = 10;
		}
		else  SleepTime = SleepTime + 50;

		PRINT_ALL_SIZE(SleepTime, InputQueueSize1, InputQueueSize2, InputQueueSize3);
		Sleep(250);

	}
}


void GenerateRandomVector()
{

	std::vector<int>temp;
	while (true) {
		srand(time(NULL));
		int i = 0;
		while (i < 1000) {
			temp.insert(temp.begin(), rand() % 10000 + 1);
			i++;
		}

		InputQueueMutex.lock();

		InputQueue1.push(temp);
		InputQueue2.push(temp);
		InputQueue3.push(temp);

		InputQueueMutex.unlock();

		temp.clear();
		Sleep(SleepTime);
	}
}

bool isQueueTooLong(int inputvectorsize, int max_size) {

	if (inputvectorsize > max_size)
		return true;

	return false;

}

void PRINT_ALL_SIZE(int sleeptime, int BubbleSortsize, int QuickSortSize, int SelectionSortSize) {
	printf("Sleep Time: %d\n", sleeptime);
	printf("Bubble Sort Queue Size :: %d\n", BubbleSortsize);
	printf("Quick Sort Queue Size :: %d\n", QuickSortSize);
	printf("Selection Sort Queue Size :: %d\n", SelectionSortSize);
	printf("----------------------\n");
}