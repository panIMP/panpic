#ifndef BASE_THREAD_H
#define BASE_THREAD_H

#include <QtCore/QThread>
#include <QtCore/QQueue>
#include <QtCore/QWaitCondition>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

#include "baseTransform.h"

class baseThread : public QThread
{
	Q_OBJECT

    baseThread(void);
    ~baseThread(void);
    baseThread(baseThread&);
    baseThread& operator = (baseThread&);

public:
    static baseThread* GetInstance();
	static void Destroy();

    void addTransform(baseTransform* trans);

signals:
	void transformStarted();
	void allTransformDone();

protected:
	void run();

private:
    static baseThread* instance;
    static baseTransform* const endTransform;

    QQueue<baseTransform*> transformQuene;
	QWaitCondition transformAdded;
	QMutex mutex;
};

#endif 
