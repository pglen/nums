; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMyEdit
LastTemplate=CEdit
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "camcli.h"
LastPage=0

ClassCount=4
Class1=CCamcliApp
Class2=CAboutDlg
Class3=CCamcliDlg

ResourceCount=2
Resource1=IDD_ABOUTBOX
Class4=CMyEdit
Resource2=IDD_CAMCLI_DIALOG

[CLS:CCamcliApp]
Type=0
BaseClass=CWinApp
HeaderFile=camcli.h
ImplementationFile=camcli.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=camcliDlg.cpp
ImplementationFile=camcliDlg.cpp
LastObject=CAboutDlg

[CLS:CCamcliDlg]
Type=0
BaseClass=CDialog
HeaderFile=camcliDlg.h
ImplementationFile=camcliDlg.cpp
Filter=W
VirtualFilter=dWC
LastObject=CCamcliDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_CAMCLI_DIALOG]
Type=1
Class=CCamcliDlg
ControlCount=12
Control1=IDOK,button,1073807361
Control2=IDCANCEL,button,1073807360
Control3=IDC_EDIT1,edit,1350635648
Control4=IDC_BUTTON1,button,1342242816
Control5=IDC_EDIT2,edit,1350635648
Control6=IDC_BUTTON2,button,1342242816
Control7=IDC_EDIT3,edit,1350635648
Control8=IDC_BUTTON3,button,1342242816
Control9=IDC_EDIT4,edit,1350635648
Control10=IDC_BUTTON4,button,1342242816
Control11=IDC_STATIC,static,1342308352
Control12=IDC_BUTTON5,button,1342242816

[CLS:CMyEdit]
Type=0
HeaderFile=MyEdit.h
ImplementationFile=MyEdit.cpp
BaseClass=CEdit
Filter=W

