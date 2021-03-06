RC=rc
LINK=link
OUTPUTDIR=dll
OBJDIR=obj

!IFNDEF RCLANGNAME
all: enu.pseudo chs.pseudo deu.pseudo esn.pseudo fra.pseudo ita.pseudo jpn.pseudo kor.pseudo ptg.pseudo
	
enu.pseudo:
	if exist $(TARGETNAME).rc $(MAKE) /$(MAKEFLAGS) /nologo -f $(MAKEFILENAME) RCLANGNAME=$*

chs.pseudo:
	if exist $(TARGETNAME).$*.rc $(MAKE) /$(MAKEFLAGS) /nologo -f $(MAKEFILENAME) RCLANGNAME=$*

deu.pseudo:
	if exist $(TARGETNAME).$*.rc $(MAKE) /$(MAKEFLAGS) /nologo -f $(MAKEFILENAME) RCLANGNAME=$*

esn.pseudo:
	if exist $(TARGETNAME).$*.rc $(MAKE) /$(MAKEFLAGS) /nologo -f $(MAKEFILENAME) RCLANGNAME=$*

fra.pseudo:
	if exist $(TARGETNAME).$*.rc $(MAKE) /$(MAKEFLAGS) /nologo -f $(MAKEFILENAME) RCLANGNAME=$*

ita.pseudo:
	if exist $(TARGETNAME).$*.rc $(MAKE) /$(MAKEFLAGS) /nologo -f $(MAKEFILENAME) RCLANGNAME=$*

jpn.pseudo:
	if exist $(TARGETNAME).$*.rc $(MAKE) /$(MAKEFLAGS) /nologo -f $(MAKEFILENAME) RCLANGNAME=$*

kor.pseudo:
	if exist $(TARGETNAME).$*.rc $(MAKE) /$(MAKEFLAGS) /nologo -f $(MAKEFILENAME) RCLANGNAME=$*

ptg.pseudo:
	if exist $(TARGETNAME).$*.rc $(MAKE) /$(MAKEFLAGS) /nologo -f $(MAKEFILENAME) RCLANGNAME=$*

!ELSE
!IF "$(RCLANGNAME)" == "enu"
RCLANGUAGE=0409
RCCODEPAGE=1252
RCLANGDESCR=English
!ELSE IF "$(RCLANGNAME)" == "chs"
RCLANGUAGE=0804
RCCODEPAGE=936
RCLANGDESCR=Simplified Chinese
!ELSE IF "$(RCLANGNAME)" == "deu"
RCLANGUAGE=0407
RCCODEPAGE=1252
RCLANGDESCR=German
!ELSE IF "$(RCLANGNAME)" == "esn"
RCLANGUAGE=0COA
RCCODEPAGE=1252
RCLANGDESCR=Spanish
!ELSE IF "$(RCLANGNAME)" == "fra"
RCLANGUAGE=040C
RCCODEPAGE=1252
RCLANGDESCR=French
!ELSE IF "$(RCLANGNAME)" == "ita"
RCLANGUAGE=0410
RCCODEPAGE=1252
RCLANGDESCR=Italian
!ELSE IF "$(RCLANGNAME)" == "jpn"
RCLANGUAGE=0411
RCCODEPAGE=932
RCLANGDESCR=Japanese
!ELSE IF "$(RCLANGNAME)" == "kor"
RCLANGUAGE=0412
RCCODEPAGE=949
RCLANGDESCR=Korean
!ELSE IF "$(RCLANGNAME)" == "ptg"
RCLANGUAGE=816
RCCODEPAGE=1252
RCLANGDESCR=Portuguese
!ELSE
!ERROR undefined language specified
!ENDIF

RC_OPTIONS=-l $(RCLANGUAGE) -c $(RCCODEPAGE) -r
RC_DEFINES=-D_X86_=1 -Di386=1 -DSTD_CALL -DCONDITION_HANDLING=1   -DNT_INST=0 -DWIN32=100 -D_NT1X_=100 -DWINNT=1 -D_WIN32_WINNT=0x0500 /DWINVER=0x0500 -D_WIN32_IE=0x0501    -DWIN32_LEAN_AND_MEAN=1 -DDEVL=1 -DDBG=1 -D__BUILDMACHINE__="" -DFPO=0  -DNDEBUG
RC_DEFINES=$(RC_DEFINES) -DVER_RESOURCE_DLL_LANGID=0x$(RCLANGUAGE),0x0000
RC_DEFINES=$(RC_DEFINES) -DNDAS_OEM_BUILD=1 
RC_DEFINES=$(RC_DEFINES) -DRCLANGDESCR="$(RCLANGDESCR)" -DRCLANGNAME="$(RCLANGNAME)"
RC=$(RC) $(RC_OPTIONS) $(RC_DEFINES) $(RC_INCLUDES)
LINK=$(LINK) -FULLBUILD -NODEFAULTLIB /WX -debug:NONE -debugtype:cv -version:5.0 -osversion:5.0 /opt:nowin98 -dll -noentry

TARGET_DLL=$(OUTPUTDIR)\$(TARGETNAME).$(RCLANGNAME).dll
TARGET_RES=$(OBJDIR)\$(TARGETNAME).$(RCLANGNAME).res
TARGET_RES_VER=$(OBJDIR)\$(TARGETNAME).$(RCLANGNAME).ver.res
!IF "$(RCLANGNAME)" == "enu"
SOURCE_RC=$(TARGETNAME).rc
!ELSE
SOURCE_RC=$(TARGETNAME).$(RCLANGNAME).rc
!ENDIF
SOURCE_RC_VER=$(TARGETNAME)_ver.rc

all: $(OUTPUTDIR) $(OBJDIR) $(TARGET_DLL) 

$(OUTPUTDIR):
	if not exist $(OUTPUTDIR) mkdir $(OUTPUTDIR)

$(OBJDIR):
	if not exist $(OBJDIR) mkdir $(OBJDIR)
	
$(TARGET_DLL): $(TARGET_RES) $(TARGET_RES_VER)
	$(LINK) -out:$@ -machine:ix86 $**

$(TARGET_RES): $(SOURCE_RC)
	$(RC) -fo $@ $**

$(TARGET_RES_VER): $(SOURCE_RC_VER)
	$(RC) -fo $@ $**

!ENDIF

clean:
	-if exist $(OUTPUTDIR) del /q $(OUTPUTDIR)\$(TARGETNAME)*.dll
	-rmdir /q $(OUTPUTDIR)
	-if exist $(OBJDIR) del /q $(OBJDIR)\$(TARGETNAME)*.res
	-rmdir /q $(OBJDIR)
