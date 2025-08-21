# doc-plugin-system
A modular and extensible C++ system for processing documents using plugins
✔️DocumentPlugin 솔루션 구조
├─ DocumentPlugin/			  #솔루션(sln)
│   ├─x64/
│         └─Release/ 			#DocumentPlugin.sln 빌드 결과물
│               ├─DocumentCore.lib
│               ├─WordCountPlugin.dll
│               ├─EncryptPlugin.dll
│               ├─JsonValidationPlugin.dll
│               ├─KeyValuePrintPlugin.dll
│        	  ├─CsvColumnSumPlugin.dll
│               └─ ...
├─ PluginManager/                      # 실행 파일(EXE)
│   ├─ PluginManager.h
│   ├─ PluginManager.cpp		#CDocument, IPugin 사용부 포함
│   └─ PluginManager.vcxproj
│
├─ DocumentCore/                   # 공통 인터페이스 (LIB)
│   ├─ DocumentCore.h            
│   ├─ DocumentCore.cpp
│   ├─ Document.h			# 문서 추상 클래스
│   ├─ IPlugin.h			# IPlugin 인터페이스 정의
│   ├─ TxtDocument.cpp
│   ├─ TxtDocument.h		
│   ├─ JsonDocument.cpp
│   ├─ JsonDocument.h
│   ├─ CsvDocument.cpp
│   ├─ CsvDocument.h
│   └─ DocumentCore.vcxproj
│
├─ WordCountPlugin/ 
│   ├─ WordCountPlugin.h
│   ├─ WordCountPlugin.cpp
│   └─ WordCountPlugin.vcxproj
│  
├─ EncryptPlugin/ 
│   ├─ EncryptPlugin.h
│   ├─ EncryptPlugin.cpp
│   └─ EncryptPlugin.vcxproj
│   
├─ JsonValidationPlugin/
│   ├─ JsonValidationPlugin.h
│   ├─ JsonValidationPlugin.cpp
│   └─ JsonValidationPlugin.vcxproj

├─ KeyValuePrintPlugin/
│   ├─ KeyValuePrintPlugin.h
│   ├─ KeyValuePrintPlugin.cpp
│   └─ KeyValuePrintPlugin.vcxproj
│
├─ CsvColumnSumPlugin/
│   ├─ CsvColumnSumPlugin.h
│   ├─ CsvColumnSumPlugin.cpp
│   └─ CsvColumnSumPlugin.vcxproj
├─ ...
│   ├─... 					#추후 플러그인 확장 가능..
└─ DocumentPlugin.sln               
