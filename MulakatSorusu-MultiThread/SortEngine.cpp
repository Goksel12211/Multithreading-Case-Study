#include "SortEngine.hpp"

using namespace Sort;



SortEngine::SortEngine(std::queue<std::vector<int>>& InputQueue, SORT_TYPE  sortType, std::mutex& mtx)
{
	mInputQueue = &InputQueue;
	mSortType = sortType;
	Mutex = &mtx;

};

static int objectMaxAmount = 3;
static int objectCurrentAmount = 0;

SortEngine* Sort::SortEngine::getInstance(std::queue<std::vector<int>>& InputQueue, SORT_TYPE sortType, std::mutex& InputQueueMutex)
{
	/////////////////////
	if (objectMaxAmount > objectCurrentAmount) {
		objectCurrentAmount++;
		obj = new SortEngine(InputQueue, sortType, InputQueueMutex);
		return obj;
	}
	else
		return NULL;

}


void SortEngine::Process()
{
	while (true)
	{
		int size = 0;
		std::vector<int> inputVector;
		Mutex->lock();
		if (!mInputQueue->empty())
			size = mInputQueue->size();


		if (size > 0) {
			inputVector = mInputQueue->front();
			mInputQueue->pop();
		}

		Mutex->unlock();

		if (size > 0) {
			switch (mSortType)
			{
			case Sort::BUBBLE:
			{
				BubbleSort(inputVector);
				break;
			}
			case Sort::QUICK:
			{
				QuickSort(inputVector);
				break;
			}
			case Sort::SELECTION:
			{
				SelectionSort(inputVector);
				break;

			}
			}
		}

	}
	Sleep(100);
}



std::vector<int> Sort::SortEngine::BubbleSort(std::vector<int> inputVector)
{

	bool swapp = true;
	while (swapp) {
		swapp = false;
		for (size_t i = 0; i < inputVector.size() - 1; i++) {
			if (inputVector[i] > inputVector[i + 1]) {
				inputVector[i] += inputVector[i + 1];
				inputVector[i + 1] = inputVector[i] - inputVector[i + 1];
				inputVector[i] -= inputVector[i + 1];
				swapp = true;
			}
		}
	}
	return inputVector;
}


std::vector<int> Sort::SortEngine::SelectionSort(std::vector<int> inputVector)
{
	int p, t;
	int MAX_SIZE = inputVector.size();
	for (int i = 0; i < MAX_SIZE; i++) {
		p = i;

		for (int j = i; j < MAX_SIZE; j++) {
			if (inputVector[p] > inputVector[j])
				p = j;
		}

		if (p != 1) {
			//Swapping Values
			t = inputVector[i];
			inputVector[i] = inputVector[p];
			inputVector[p] = t;
		}

	}

	return inputVector;
}

std::vector<int>Sort::SortEngine::QuickSort(std::vector<int>& vec) {

	std::vector<int> vektör = vec;

	quickhelper(vektör, 0, vektör.size() - 1);

	return vektör;

}

void Sort::SortEngine::quickhelper(std::vector<int>& vec, int L, int R) {
	int i, j, mid, piv;
	i = L;
	j = R;
	mid = L + (R - L) / 2;
	piv = vec[mid];
	while (i<R || j>L) {
		while (vec[i] < piv)
			i++;
		while (vec[j] > piv)
			j--;

		if (i <= j) {
			swap(vec, i, j); //error=swap function doesnt take 3 arguments
			i++;
			j--;
		}
		else {
			if (i < R)
				quickhelper(vec, i, R);
			if (j > L)
				quickhelper(vec, L, j);
			return;
		}

	}

}


void Sort::SortEngine::swap(std::vector<int>& v, int x, int y) {
	int temp = v[x];
	v[x] = v[y];
	v[y] = temp;

}