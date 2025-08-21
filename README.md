# doc-plugin-system
### A modular and extensible C++ system for processing documents using plugins
## 📜DocumentPlugin 솔루션 구조
<img width="384" height="837" alt="image" src="https://github.com/user-attachments/assets/4f003508-9fc4-473b-a517-bcd1fd83f82b" />

## ⚙️클래스 다이어그램
<img width="1205" height="595" alt="플러그인 drawio" src="https://github.com/user-attachments/assets/2653b739-2bab-42a1-89d6-40610ece9081" />

## ✔️플러그인 추가 시 방법
### 1. 만약, EncryptionPlugin.dll 플러그인을 통해 TXT파일을 암호화 했던 문서를 복호화하는 기능의 플러그인을 추가한다고 가정한다.
### 2. DecryptionPlugin.dll 플러그인 프로젝트 생성 후 구현한다.
#### 2-1. IPlugin 인터페이스를 상속받아 구현한다.
#### 2-2. extern "C"를 사용하여 아래와 같이 CreatePlugin, DestroyPlugin를 구현해준다.
##### extern "C" __declspec(dllexport) IPlugin* CreatePlugin() {
##### 	return new CDecryptionPlugin();
##### }
##### extern "C" __declspec(dllexport) void DestroyPlugin(IPlugin* p) {
#####  delete p;
#####  }
### 3. ../x64/Release/plugins.ini 파일에 Plugin6=DecryptionPlugin.dll 을 추가해준다.
<img width="214" height="124" alt="image" src="https://github.com/user-attachments/assets/aacc4137-5a66-457a-a3e5-adf6da1f19e9" />

### 4. PluginManager.exe를 실행해주면 자동으로 DecryptionPlugin.dll 까지 로딩되어 원하는 기능이 동작한다.

