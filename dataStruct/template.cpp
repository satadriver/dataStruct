template <typename T>

T myTemplateTest(T t) {
	return t;
}



void templateTest() {

	long ret = myTemplateTest<long>(0);

	return;
}