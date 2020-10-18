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
/* �ǽ�(1-1) �м���� : Exception�� ���� �� ���������� �����ϴ� ���

Executed in B		     // main() �Լ��� sub function���� ȣ��Ǹ� main()�� funcA()�� ȣ��, funcA()�� Test ��ü ���� �� funcB() ȣ��, funcB()�� ����Ǹ� �޼��� ȣ���ϰ� ����
Destructor execution: B  // funcB() ����Ǹ� Test�� ��ü r('B')�� �����Ǿ�����, �Լ��� ����Ǹ� Destructor�� ��ü �Ҹ�
Executed in A			 // funcB() ������ �ڽ��� ȣ���� �����Լ��� �̵��Ͽ� funcA() ����
Destructor execution: A  // funcA() �Լ� ����Ǹ� funcA�� ��ü�� r('A') destructor�� �Ҹ�


 �ǽ�(1-2) �м���� : Exception�� �߻��ϴ� ���

Destructor execution: B				// main() �Լ��� funcA()ȣ��, funcA()�� funcB()ȣ��, funcB() ������ ���� �߻��ϰ� funcB()�� ��ü�� �Ҹ�
Destructor execution: A				// funcB()�� �ڽ��� ȣ���� funcA()�� ������ ��� ����(Stack unwinding)�ϸ� funcA�� ���ǵ� ��ü �Ҹ�
Exception : Exception from funcB!	// funcA()�� ���ܸ� �޴� catch���� ���⿡, funcB()�κ��� ���� ���ܸ� �ٽ� main()�� ����ó���������� ���� catch�� ���ܸ� ����.

funcB���� ���ܰ� �߻��Ͽ�����, funcB�� funcA�� ȣ���ϰ�, funcA�� main���� ȣ���Ͽ���.
������, funcA�� ���ܸ� �޴� catch������ ���⿡ ���ܴ� catch���� �ִ� main���� ���ĵȴ�.
���ĵǴ� �������� �ٷ� catch�� ���� �ϸ鼭, �� �Լ��� ���� �Ǿ��� ��ü�� �����ϰ�(stack unwinding),
���ܴ� main�� �ִ� catch�������� ���޵Ǿ� ��µǾ���.
��ó�� stack unwinding�̶� catch�� �����ϸ鼭 stack�� ���ǵ� ��ü���� �����ϴ� ���� ���ϸ�,
stack unwinding�� ����Ǹ� ������ ����Ǵ� �ڵ���� �����ǰ� �ٷ� exception handler�� �ִ� ������ ���� �帧�� �ٲ��.

*/