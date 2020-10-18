#include <iostream>
#include <stdexcept>
class Test {
public:
	Test(char id) : id_(id) {}
	~Test() {
		std::cout << "Destructor execution: "
			<< id_ << std::endl;
	}
private:
	char id_;
};
int funcB() {
	Test r('B');
	throw std::runtime_error("Exception from funcB!\n");
	std::cout << "Executed in B" << std::endl;
	return 0;
}
int funcA() {
	Test r('A');
	funcB();
	std::cout << "Executed in A" << std::endl;
	return 0;
}
int main() {
	try {
		funcA();
	}
	catch (std::exception& e) {
		std::cout << "Exception : " << e.what();
	}
}
/* 실습(1-1) 분석결과 : Exception이 없을 때 정상적으로 실행하는 경우

Executed in B		     // main() 함수의 sub function들이 호출되며 main()가 funcA()를 호출, funcA()는 Test 객체 만든 후 funcB() 호출, funcB()가 실행되며 메세지 호출하고 리턴
Destructor execution: B  // funcB() 실행되며 Test의 객체 r('B')가 생성되었으나, 함수가 종료되며 Destructor로 객체 소멸
Executed in A			 // funcB() 끝나면 자신을 호출한 상위함수로 이동하여 funcA() 실행
Destructor execution: A  // funcA() 함수 종료되며 funcA의 객체인 r('A') destructor로 소멸


 실습(1-2) 분석결과 : Exception이 발생하는 경우

Destructor execution: B				// main() 함수가 funcA()호출, funcA()는 funcB()호출, funcB() 내에서 예외 발생하고 funcB()의 객체도 소멸
Destructor execution: A				// funcB()는 자신을 호출한 funcA()의 스택을 모두 해제(Stack unwinding)하며 funcA에 정의된 객체 소멸
Exception : Exception from funcB!	// funcA()는 예외를 받는 catch문이 없기에, funcB()로부터 받은 예외를 다시 main()의 예외처리영역으로 던져 catch가 예외를 받음.

funcB에서 예외가 발생하였으나, funcB는 funcA가 호출하고, funcA는 main에서 호출하였다.
하지만, funcA는 예외를 받는 catch구문이 없기에 예외는 catch문이 있는 main까지 전파된다.
전파되는 과정에서 바로 catch로 점프 하면서, 각 함수에 정의 되었던 객체만 해제하고(stack unwinding),
예외는 main에 있는 catch구문까지 전달되어 출력되었다.
이처럼 stack unwinding이란 catch로 점프하면서 stack에 정의된 객체들을 해제하는 것을 말하며,
stack unwinding이 실행되며 기존에 실행되던 코드들이 생략되고 바로 exception handler가 있는 곳으로 실행 흐름이 바뀐다.

*/