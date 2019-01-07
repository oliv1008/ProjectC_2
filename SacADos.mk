##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=SacADos
ConfigurationName      :=Debug
WorkspacePath          :=/home/olivier/Bureau/Polytech/ProjetC_2/SacADos
ProjectPath            :=/home/olivier/Bureau/Polytech/ProjetC_2/SacADos
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Olivier
Date                   :=05/01/19
CodeLitePath           :=/home/olivier/.codelite
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="SacADos.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/source_recherche_locale.c$(ObjectSuffix) $(IntermediateDirectory)/main.c$(ObjectSuffix) $(IntermediateDirectory)/parser.c$(ObjectSuffix) $(IntermediateDirectory)/source_codage.c$(ObjectSuffix) $(IntermediateDirectory)/source_heuristique.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/source_recherche_locale.c$(ObjectSuffix): source/recherche_locale.c $(IntermediateDirectory)/source_recherche_locale.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/olivier/Bureau/Polytech/ProjetC_2/SacADos/source/recherche_locale.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/source_recherche_locale.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/source_recherche_locale.c$(DependSuffix): source/recherche_locale.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/source_recherche_locale.c$(ObjectSuffix) -MF$(IntermediateDirectory)/source_recherche_locale.c$(DependSuffix) -MM source/recherche_locale.c

$(IntermediateDirectory)/source_recherche_locale.c$(PreprocessSuffix): source/recherche_locale.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/source_recherche_locale.c$(PreprocessSuffix) source/recherche_locale.c

$(IntermediateDirectory)/main.c$(ObjectSuffix): main.c $(IntermediateDirectory)/main.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/olivier/Bureau/Polytech/ProjetC_2/SacADos/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.c$(DependSuffix): main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.c$(ObjectSuffix) -MF$(IntermediateDirectory)/main.c$(DependSuffix) -MM main.c

$(IntermediateDirectory)/main.c$(PreprocessSuffix): main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.c$(PreprocessSuffix) main.c

$(IntermediateDirectory)/parser.c$(ObjectSuffix): parser.c $(IntermediateDirectory)/parser.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/olivier/Bureau/Polytech/ProjetC_2/SacADos/parser.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/parser.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/parser.c$(DependSuffix): parser.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/parser.c$(ObjectSuffix) -MF$(IntermediateDirectory)/parser.c$(DependSuffix) -MM parser.c

$(IntermediateDirectory)/parser.c$(PreprocessSuffix): parser.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/parser.c$(PreprocessSuffix) parser.c

$(IntermediateDirectory)/source_codage.c$(ObjectSuffix): source/codage.c $(IntermediateDirectory)/source_codage.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/olivier/Bureau/Polytech/ProjetC_2/SacADos/source/codage.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/source_codage.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/source_codage.c$(DependSuffix): source/codage.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/source_codage.c$(ObjectSuffix) -MF$(IntermediateDirectory)/source_codage.c$(DependSuffix) -MM source/codage.c

$(IntermediateDirectory)/source_codage.c$(PreprocessSuffix): source/codage.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/source_codage.c$(PreprocessSuffix) source/codage.c

$(IntermediateDirectory)/source_heuristique.c$(ObjectSuffix): source/heuristique.c $(IntermediateDirectory)/source_heuristique.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/olivier/Bureau/Polytech/ProjetC_2/SacADos/source/heuristique.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/source_heuristique.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/source_heuristique.c$(DependSuffix): source/heuristique.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/source_heuristique.c$(ObjectSuffix) -MF$(IntermediateDirectory)/source_heuristique.c$(DependSuffix) -MM source/heuristique.c

$(IntermediateDirectory)/source_heuristique.c$(PreprocessSuffix): source/heuristique.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/source_heuristique.c$(PreprocessSuffix) source/heuristique.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


