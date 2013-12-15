#include "baseThread.h"

baseTransform* const baseThread::endTransform = 0;
baseThread* baseThread::instance = 0;

baseThread::baseThread(void)
{
	start();
}


baseThread::~baseThread(void)
{
	{
		QMutexLocker locker(&mutex);
		while (!transformQuene.isEmpty())
		{
			delete transformQuene.dequeue();
		}

		// mark the empty event of the transaction queue to restore ui state
		transformQuene.enqueue(endTransform);
		transformAdded.wakeOne();
	}

	wait();
}

baseThread* baseThread::GetInstance()
{
	if (instance == 0)
	{
		instance = new baseThread();
	}

	return instance;
}

void baseThread::Destroy()
{
	if (instance != 0)
	{
		delete instance;
		instance = 0;
	}
}

void baseThread::addTransform(baseTransform* trans)
{
	QMutexLocker locker(&mutex);
	transformQuene.enqueue(trans);
	transformAdded.wakeOne();
}

void baseThread::run()
{
	baseTransform* curTransform = 0;

	forever
	{
		{
			//	get transform from the transform queue
			//	if there is no transform in the quene, wait
			QMutexLocker locker(&mutex);

			if (transformQuene.isEmpty())
			{
				transformAdded.wait(&mutex);
			}

			//	if there is still transform undone, get the transform 	
			curTransform = transformQuene.dequeue();

			//	if the transform is endTransform, break the forever loop, thus run function ends
			if (curTransform == endTransform)
			{
				break;
			}
		}

		//	delet the transform after transform done
		emit transformStarted();
		curTransform->apply();
		delete curTransform;

		//	after deleting the transform fetched out just now, check the transform queue again
		//	if there is no transform in the queue, signal that all transfom done
		{
			QMutexLocker locker(&mutex);
			if (transformQuene.isEmpty())
			{
				emit allTransformDone();
			}
		}
	}
}
