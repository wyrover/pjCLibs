#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

//#define __DEBUG_PJPATH__
//#define __DEBUG_PJSTRING__
//#define __DEBUG_PJTEXTREADER__
//#define __DEBUG_PJTEXTWRITER__
//#define __DEBUG_PJJPEGFILE__
#define __DEBUG_PJSERIALPORT__

#ifdef __DEBUG_PJSERIALPORT__
#include "pjSerialPort.h"
#endif

#ifdef __DEBUG_PJJPEGFILE__
#include "pjJpegFile.h"
#endif

#ifdef __DEBUG_PJTEXTWRITER__
#include "pjTextWriter.h"
#endif

#ifdef __DEBUG_PJTEXTREADER__
#include "pjTextReader.h"
#endif

#ifdef __DEBUG_PJPATH__
#include "pjPath.h"
#endif

#ifdef __DEBUG_PJSTRING__
#include "pjString.h"
#endif

#ifdef __DEBUG_PJSERIALPORT__
void SendDataWithLineEnd( void ){
    char send[25];
    printf("Send String: ");  
    scanf("%s", send);
    pjSerialPort_WriteLine( send );
}

void SendData( void ){
    char send[25];
    printf("Send String: ");  
    scanf("%s", send);
    pjSerialPort_WriteData( send ); 
}

void Exit( void ){
    pjSerialPort_ClosePort();
    exit(0);   
}
#endif

int main(int argc, char *argv[])
{
#ifdef __DEBUG_PJSERIALPORT__
    long int version = pjSerialPort_GetVersion();
    printf("pjSerialPort Ver: %d.%d.%d\n", version>>16&0xff, version>>8&0xff, version&0xff);
    printf("pjSerialPort Ver: %d.%d.%d\n", pjSerialPort_GetVersionMajor(), pjSerialPort_GetVersionMinor(), pjSerialPort_GetVersionPatch());
    
    pjSerialPort_Initialize();
    pjSerialPort_OpenPort( 4, 115200, 0, 8, 0 );
    pjSerialPort_Callback* callbacks = (pjSerialPort_Callback*)malloc(sizeof(pjSerialPort_Callback)*3);
    callbacks[0] = SendDataWithLineEnd;
    callbacks[1] = SendData;
    callbacks[2] = Exit;
    if( pjSerialPort_IsOpened() ){
        printf("open port passed.\n");
        while( !kbhit() ){
            printf("%s", pjSerialPort_ReadLineWithCallbacks( "sge", callbacks ) );   
        }
        pjSerialPort_ClosePort();
    }else{
        printf("open port failed.\n");
    }
    free( callbacks );
#endif

#ifdef __DEBUG_PJJPEGFILE__
    if( pjJpegFile_IsLibJpegExist() ){
        long int version = pjJpegFile_GetVersion();
        printf("pjJpegFile Version: %d.%d.%d\n", version>>16&0xff, version>>8&0xff, version&0xff);
        printf("pjJpegFile Version: %d.%d.%d\n", pjJpegFile_GetVersionMajor(), pjJpegFile_GetVersionMinor(), pjJpegFile_GetVersionPatch());
        
        pjJpegFile* jpegFile = (pjJpegFile*)malloc(sizeof(pjJpegFile));
    
        pjJpegFile_ReadFile( "flower.jpg", jpegFile );
        int c = 0, r = 0;
        printf("GetPixel Pos: ");
        scanf("%d,%d",&r,&c);
        pjJpegColor clr = pjJpegFile_GetPixel( jpegFile, r, c );
        printf("%d,%d,%d\n", clr.R, clr.G, clr.B );
        clr.R = 255;
        clr.G = 0;
        clr.B = 255;
        pjJpegFile_SetRegionColor( jpegFile, c+5, r+5, 100,100, clr);
        clr.R = 0;
        clr.G = 0;
        clr.B = 0;
        pjJpegFile_SetPixel( jpegFile, 20, 20, clr );
        pjJpegFile_WriteFile( jpegFile, "flower2.jpg", 75 );
        
        pjJpegFile_Dispose( jpegFile );
        free(jpegFile);
    }else{
        printf("jpeg62.dll is not exist.\n");  
    }
#endif

#ifdef __DEBUG_PJTEXTWRITER__
    long int version = pjTextWriter_GetVersion();
    printf("pjTextWriter Version: %d.%d.%d\n", version>>16&0xff, version>>8&0xff, version&0xff);
    printf("pjTextWriter Version: %d.%d.%d\n", pjTextWriter_GetVersionMajor(), pjTextWriter_GetVersionMinor(), pjTextWriter_GetVersionPatch());
    
    pjTextWriter* textWriter = (pjTextWriter*)malloc(sizeof(pjTextWriter));
    char buffer[8] = "dded";
    
    pjTextWriter_OpenFile( textWriter, "C:\\a.txt" );
    pjTextWriter_WriteLine( textWriter, "abcd" );
    pjTextWriter_WriteChars( textWriter, buffer );
    pjTextWriter_WriteLine( textWriter, "123");
    pjTextWriter_CloseFile( textWriter );
    
    free(textWriter);
    textWriter = NULL;
#endif

#ifdef __DEBUG_PJTEXTREADER__
    long int version = pjTextReader_GetVersion();
    printf("pjTextReader Version: %ld.%d.%d\n", version>>16&0xff, version>>8&0xff, version&0xff);
    printf("pjTextReader Version: %d.%d.%d\n", pjTextReader_GetVersionMajor(),pjTextReader_GetVersionMinor(),pjTextReader_GetVersionPatch());
    
    pjTextReader* textReader = (pjTextReader*)malloc(sizeof(pjTextReader));
    char line[9];
    pjTextReader_OpenFile( textReader, "a.txt" );
    printf("GetLineNumber: %d\n", pjTextReader_GetLineNumber( textReader ) );
    printf("MaxLineLength: %d\n", pjTextReader_GetMaxLineLength( textReader ) );
    pjTextReader_ReadChars( textReader, 6, line);
    printf("ReadChars: %s\n", line);
    pjTextReader_ReadLine( textReader, line );
    printf("ReadLine: %s\n", line );
    pjTextReader_ReadLine( textReader, line );
    printf("ReadLine: %s\n", line );
    pjTextReader_ReadLine( textReader, line );
    printf("ReadLine: %s\n", line );
    pjTextReader_CloseFile( textReader );
    free(textReader );
#endif

#ifdef __DEBUG_PJPATH__
	long int version = pjPath_GetVersion();
	printf("pjPath Version: %ld.%d.%d\n", version>>16&0xff, version>>8&0xff, version&0xff);
	printf("pjPath Version: %d.%d.%d\n", pjPath_GetVersionMajor(), pjPath_GetVersionMinor(), pjPath_GetVersionPatch() );
	
	char fileExt[6];
	pjPath_GetFileExtension("C:\\a.txt",fileExt);
	printf("GetFileExtension: %s\n", fileExt);
	
	char dirName[128];
	pjPath_GetDirectoryName("C:\\pengjun\\abc\\d.pdf",dirName);
	printf("GetDirectoryName: %s\n", dirName);
	
	char fileName[12];
	pjPath_GetFileName("C:\\pengjun\\a\\b\\c\\defs.sdf",fileName);
	printf("FileName: %s\n", fileName);
	pjPath_GetFileNameWithoutExtension("C:\\pengjun\\a\\dsf.dd",fileName);
	printf("FileName: %s\n", fileName);
	
	pjPath_GetDriveName("C:\\pengjun\\abc\\dedfs.dff",fileName);
	printf("DriveName: %s\n", fileName);
#endif

#ifdef __DEBUG_PJSTRING__
    long int version = pjString_GetVersion();
	printf("pjString Version: %ld.%d.%d\n", version>>16&0xff, version>>8&0xff, version&0xff);
	printf("pjString Version: %d.%d.%d\n", pjString_GetVersionMajor(), pjString_GetVersionMinor(), pjString_GetVersionPatch() );
	
	char* testString = "abcd1389c";
	printf("Length: %d\n", pjString_Length(testString) );
	printf("Find: %d\n", pjString_Find(testString,'1'));
	
	char* testStr = (char*)malloc(sizeof(char)*strlen(testString));
	memset(testStr,'\0',sizeof(char)*strlen(testString));
	pjString_Copy( testStr, testString );
	printf("Copy: %s\n", testStr);
	pjString_Replace( testStr, 'c', 'e' );
	printf("Replace: %s\n", testStr );
	pjString_CopyLimited( testStr, testString, pjString_Length(testString)-3);
	printf("CopyLimited: %s\n", testStr);
	pjString_Append( testStr, "peng" );
	printf("Append: %s\n", testStr );
	char* subStr = (char*)malloc(sizeof(char)*5);
	pjString_Substring(testStr,2,5,subStr);
	printf("Substring: %s\n", subStr);
	int* find = (int*)malloc(sizeof(int)*5);
	int num = pjString_FindAll( testString, 'c', find );
	int i = 0;
	for(i=0;i<num;i++)
		printf(" %d ", find[i]);
	free(find);
	free(subStr);
	free(testStr);
#endif
	
	system("pause");
	return 0;
}
