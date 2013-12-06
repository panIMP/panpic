#ifndef TRANSACTIONTHREAD_H
#define TRANSACTIONTHREAD_H

#include <QtCore/QThread>
#include <QtCore/QQueue>
#include <QtCore/QWaitCondition>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

#include "transform.h"

class TransformThread : public QThread
{
	Q_OBJECT

public:
	TransformThread(void);
	~TransformThread(void);

	void addTransform(Transform* trans);

signals:
	void transformStarted();
	void allTransformDone();

protected:
	void run();

private:
	static Transform* const endTransform;  

	QQueue<Transform*> transformQuene;
	QWaitCondition transformAdded;
	QMutex mutex;
};

#endif 