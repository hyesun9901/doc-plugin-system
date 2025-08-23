# doc-plugin-system
### A modular and extensible C++ system for processing documents using plugins
## 📜DocumentPlugin 솔루션 구조
<img width="423" height="807" alt="image" src="https://github.com/user-attachments/assets/3faebe65-47e2-4710-847f-53a4654825ef" />


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

### 3. PluginManager 클래스의 함수 register_plugin vs register_plugin_all
#### 3.1 register_plugin 사용할 경우(더 안전함)
##### ../x64/Release/plugins.ini 파일에 Plugin6=DecryptionPlugin.dll 을 추가해준다.
<img width="214" height="124" alt="image" src="https://github.com/user-attachments/assets/aacc4137-5a66-457a-a3e5-adf6da1f19e9" />

##### ⚠️제품이라면 plugins.ini 파일을 암호화하여 사용하는 것이 더 안전할 것

#### 3.2 register_plugin_all 사용할 경우
##### 자동으로 실행 프로그램의 경로 내 모든 dll을 로드해주므로 ../x64/Release/plugins.ini 파일 수정이 필요없다.
##### plugin 모듈을 모아둔 경로를 추가해서 사용하는 방식이 더 안전할 것이다.
##### ⚠️제품이라면 해당 폴더는 자체보호를 걸어 의도하지 않은 모듈이 등록되지 않도록 할 것

### 4. PluginManager.exe를 실행해주면 자동으로 DecryptionPlugin.dll 까지 로딩되어 원하는 기능이 동작한다.

