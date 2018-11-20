빌드 시 출력에 호환 관련 오류가 있다면?
-비주얼 스튜디오 상단의 프로젝트 -> 프로젝트 속성 -> 구성 속성 -> 일반 -> Windows SDK버전 10.0.15xxx로 변경

OpenGL32.dll을 찾을 수 없습니다 오류가 난다면?
- OpenGL32.dll을 C:\Windows\System32 폴더로 이동

GL/gl.h를 찾을 수 없습니다 오류가 난다면?
- 비주얼 스튜디오 상단의 프로젝트 -> 프로젝트 속성 -> 구성 속성 -> 일반 -> Windows SDK버전 10.0.16xxx로 변경
- 10.0.16xxx가 없거나 변경 해도 오류가 난다면
  ->Runaway폴더 속의 GL폴더를
	C:\Program Files (x86)\Windows Kits\10\Include에서 현재 사용중인 SDK버전 폴더->um로 이동