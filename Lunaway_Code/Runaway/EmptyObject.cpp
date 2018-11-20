#include "stdafx.h"
#include "EmptyObject.h"
#include "TestScene2.h"

//빈 오브젝트를 사용할 경우 useModel을 비활성화 해야합니다.

EmptyObject::EmptyObject()
{
	useModel = false;
}


EmptyObject::~EmptyObject()
{
}

void EmptyObject::Update() {
	

}