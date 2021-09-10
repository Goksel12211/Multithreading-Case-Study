#include <queue>
#include <iostream>
#include <Windows.h>
#include <thread> 
#include <mutex>

namespace Sort
{
	enum SORT_TYPE { BUBBLE = 0, QUICK = 1, SELECTION = 2 };

	class SortEngine
	{
	public:
		void Process();
		static SortEngine* getInstance(std::queue<std::vector<int>>& InputQueue, SORT_TYPE sortType, std::mutex& InputQueueMutex);

	private:
		static SortEngine* obj;
		SortEngine(std::queue<std::vector<int>>& InputQueue, SORT_TYPE sortType, std::mutex& InputQueueMutex);
		std::vector<int> BubbleSort(std::vector<int> inputVector);
		std::vector<int> SelectionSort(std::vector<int> inputVector);
		//std::vector<int> Quicksort(std::vector<int>& vec, int L, int R);
		std::queue<std::vector<int>>* mInputQueue;
		SORT_TYPE mSortType;
		std::mutex* Mutex;
		void swap(std::vector<int>& v, int x, int y);
		void quickhelper(std::vector<int>& vec, int L, int R);
		std::vector<int> QuickSort(std::vector<int>& vec);

	};
}
