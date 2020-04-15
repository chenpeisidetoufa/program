#include <thread>
#include <iostream>
#include <mutex>

using namespace std;

int a = 0;
mutex locker;

void ThreadFun1()
{
	locker.lock();
	cout << "线程1的id为： " << this_thread::get_id() << endl;
	cout << "线程1正在执行" << endl;
	this_thread::sleep_for(std::chrono::milliseconds(1000 * 10));
	cout << a << endl;
	locker.unlock();
}

void ThreadFun2()
{
	locker.lock();
	cout << "线程2的id为： " << this_thread::get_id() << endl;
	cout << "线程2正在执行" << endl;
	this_thread::sleep_for(std::chrono::milliseconds(1000 * 10));
	cout << a << endl;
	locker.unlock();
}

int main()
{
	cout << "主线程的线程id为： " << this_thread::get_id() << endl;
	mutex locker;
	thread t1(ThreadFun1);
	thread t2(ThreadFun2);
	t1.detach();
	t2.detach();
	this_thread::sleep_for(std::chrono::milliseconds(1000 * 30));
	return 0;
}
