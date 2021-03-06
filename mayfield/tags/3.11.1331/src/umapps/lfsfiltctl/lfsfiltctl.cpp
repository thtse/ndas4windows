/*++

Copyright (C) 2002-2004 XIMETA, Inc.
All rights reserved.

Initial implementation:

2004-8-15 Chesong Lee <cslee@ximeta.com>

Revisons:

--*/

#define STRICT
#include <windows.h>
#include <tchar.h>
#include <winioctl.h>
#include <strsafe.h>
#include <crtdbg.h>

#include "lfsfiltctl.h"

#include "lfsfilterpublic.h"
#include <xtl/xtlautores.h>

#define XDBG_LIBRARY_MODULE XDF_LFSFILTCTL
#include "xdebug.h"

const LPCTSTR LFSFILT_DEVICE_NAME = _T("\\\\.\\Global\\lfsfilt");
const LPCTSTR LFSFILT_DRIVER_NAME = _T("lfsfilt.sys");
const LPCTSTR LFSFILT_SERVICE_NAME = _T("lfsfilt");

/*++

LfsFiltCtlStartService with SCM handle

--*/
BOOL 
WINAPI 
LfsFiltCtlStartService(SC_HANDLE hSCManager)
{
	XTL::AutoSCHandle hService = ::OpenService(
		hSCManager,
		LFSFILT_SERVICE_NAME,
		GENERIC_READ | GENERIC_EXECUTE);

	if (hService.IsInvalid()) 
	{
		DPErrorEx(_FT("Opening a service (%s) failed: "), LFSFILT_SERVICE_NAME);
		return FALSE;
	}

	BOOL fSuccess = ::StartService(hService, 0, NULL);
	if (!fSuccess) 
	{
		DPErrorEx(_FT("Starting a service (%s) failed: "), LFSFILT_SERVICE_NAME);
		return FALSE;
	}

	DPInfo(_FT("LFS Filter service started successfully.\n"));
	return TRUE;
}

/*++

LfsFiltCtlQueryServiceStatus without SCM handle

--*/
BOOL
WINAPI 
LfsFiltCtlStartService()
{
	XTL::AutoSCHandle hSCManager = ::OpenSCManager(
		NULL, 
		SERVICES_ACTIVE_DATABASE, 
		GENERIC_READ);

	if (hSCManager.IsInvalid()) 
	{
		DPErrorEx(_FT("Failed to open SCM Database.\n"));
		return FALSE;
	}

	return LfsFiltCtlStartService(hSCManager);
}

/*++

LfsFiltCtlQueryServiceStatus with SCM handle

--*/
BOOL 
WINAPI 
LfsFiltCtlQueryServiceStatus(
	SC_HANDLE hSCManager,
	LPSERVICE_STATUS lpServiceStatus)
{
	XTL::AutoSCHandle hService = ::OpenService(
		hSCManager,
		LFSFILT_SERVICE_NAME,
		GENERIC_READ | GENERIC_EXECUTE);

	if (hService.IsInvalid()) 
	{
		DPErrorEx(_FT("Opening Service (%s) failed: "), LFSFILT_SERVICE_NAME);
		return FALSE;
	}

	BOOL fSuccess = ::QueryServiceStatus(hService, lpServiceStatus);
	if (!fSuccess) 
	{
		DPErrorEx(_FT("Querying Service Status (%s) failed: "), LFSFILT_SERVICE_NAME);
		return FALSE;
	}

	DPInfo(_FT("QueryServiceStatus succeeded.\n"));
	return TRUE;
}


/*++

NdasRoFilterQueryServiceStatus without SCM handle

--*/
BOOL 
WINAPI 
LfsFiltCtlQueryServiceStatus(
	LPSERVICE_STATUS lpServiceStatus)
{
	XTL::AutoSCHandle hSCManager = ::OpenSCManager(
		NULL, 
		SERVICES_ACTIVE_DATABASE, 
		GENERIC_READ);

	if (hSCManager.IsInvalid()) 
	{
		DPErrorEx(_FT("Opening SCM Database failed: "));
		return FALSE;
	}

	return LfsFiltCtlQueryServiceStatus(hSCManager, lpServiceStatus);
}

/*++

LfsFiltCtlOpenDevice

Create a handle for LFSFilt device object,
If failed, returns INVALID_HANDLE_VALUE

--*/
HANDLE 
WINAPI 
LfsFiltCtlOpenDevice()
{
	//
	// Returning handle must not be AutoFileHandle
	//
	HANDLE hDevice = ::CreateFile(
		LFSFILT_DEVICE_NAME,
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (INVALID_HANDLE_VALUE == hDevice) 
	{
		DPErrorEx(_FT("Opening %s failed: "), LFSFILT_DEVICE_NAME);
		return INVALID_HANDLE_VALUE;
	}

	return hDevice;
}

/*++

Get the version information of LFS Filter
This IOCTL supports since Rev 1853

--*/

BOOL 
WINAPI 
LfsFiltCtlGetVersion(
	HANDLE hFilter,
	LPWORD lpwVerMajor, LPWORD lpwVerMinor,
	LPWORD lpwVerBuild, LPWORD lpwVerPrivate,
	LPWORD lpwNDFSVerMajor, LPWORD lpwNDFSVerMinor)
{
	DWORD cbReturned = 0;
	LFSFILT_VER verInfo = {0};

	BOOL fSuccess = ::DeviceIoControl(
		hFilter,
		LFS_FILTER_GETVERSION,
		NULL, 0,
		&verInfo, sizeof(verInfo), &cbReturned,
		(LPOVERLAPPED) NULL);

	if (!fSuccess) 
	{
		DPErrorEx(_FT("Getting LfsFilter Version failed: "));
		return FALSE;
	}

	if (lpwVerMajor) *lpwVerMajor = verInfo.VersionMajor;
	if (lpwVerMinor) *lpwVerMinor = verInfo.VersionMinor;
	if (lpwVerBuild) *lpwVerBuild = verInfo.VersionBuild;
	if (lpwVerPrivate) *lpwVerPrivate = verInfo.VersionPrivate;
	if (lpwNDFSVerMajor) *lpwNDFSVerMajor = verInfo.VersionNDFSMajor;
	if (lpwNDFSVerMinor) *lpwNDFSVerMinor = verInfo.VersionNDFSMinor;

	DPInfo(_FT("LfsFilter version is %d.%d.%d.%d, NDFS %d.%d\n"), 
		verInfo.VersionMajor, verInfo.VersionMinor,
		verInfo.VersionBuild, verInfo.VersionPrivate,
		verInfo.VersionNDFSMajor, verInfo.VersionNDFSMinor);

	return TRUE;
}

BOOL 
WINAPI 
LfsFiltCtlGetVersion(
	LPWORD lpwVerMajor, 
	LPWORD lpwVerMinor,
	LPWORD lpwVerBuild,
	LPWORD lpwVerPrivate,
	LPWORD lpwNDFSVerMajor,
	LPWORD lpwNDFSVerMinor)
{
	XTL::AutoFileHandle hDevice = LfsFiltCtlOpenDevice();

	if (hDevice.IsInvalid()) 
	{
		DPErrorEx(_FT("Opening %s failed: "), LFSFILT_DEVICE_NAME);
		return FALSE;
	}

	return LfsFiltCtlGetVersion(
		hDevice, 
		lpwVerMajor, lpwVerMinor,
		lpwVerBuild, lpwVerPrivate,
		lpwNDFSVerMajor, lpwNDFSVerMinor);
}
/*++

Shutdown LfsFilter

Explicit call to shut down LfsFilter when shutting down the system.

--*/
BOOL WINAPI LfsFiltCtlShutdown(HANDLE hFilter)
{
	DWORD cbReturned = 0;
	BOOL fSuccess = ::DeviceIoControl(
		hFilter,
		LFS_FILTER_SHUTDOWN,
		NULL, 0,
		NULL, 0, &cbReturned,
		(LPOVERLAPPED) NULL);
	
	if (!fSuccess) 
	{
		DPErrorEx(_FT("Shutting down LfsFilter failed: "));
		return FALSE;
	}

	DPInfo(_FT("LfsFilter is shut down successfully.\n"));
	return TRUE;
}


/*++

Create an event queue in LfsFilt

--*/
BOOL 
WINAPI 
LfsFiltCtlCreateEventQueue(
		IN HANDLE				hFilter,
		OUT PLFS_EVTQUEUE_HANDLE	LfsEventQueueHandle,
		OUT HANDLE				*LfsEventWait)
{
	DWORD cbReturned = 0;
	LFS_CREATEEVTQ_RETURN	createEvetqReturn;

	BOOL fSuccess = ::DeviceIoControl(
		hFilter,
		LFS_FILTER_CREATE_EVTQ,
		NULL, 0,
		&createEvetqReturn, sizeof(createEvetqReturn), &cbReturned,
		(LPOVERLAPPED) NULL);

	if (!fSuccess) 
	{
		DPErrorEx(_FT("Creating an event queue failed: "));
		return FALSE;
	}

	if (LfsEventQueueHandle) *LfsEventQueueHandle = 
				(LFS_EVTQUEUE_HANDLE)createEvetqReturn.EventQueueHandle;
	if (LfsEventWait) *LfsEventWait = createEvetqReturn.EventWaitHandle;

	DPInfo(_FT("LfsFilter event queue created is %p %p\n"), 
		createEvetqReturn.EventQueueHandle,
		createEvetqReturn.EventWaitHandle);

	return TRUE;
}

BOOL 
WINAPI 
LfsFiltCtlCreateEventQueue(
		OUT LFS_EVTQUEUE_HANDLE	*LfsEventQueueHandle,
		OUT HANDLE				*LfsEventWait
){
	XTL::AutoFileHandle hDevice = LfsFiltCtlOpenDevice();

	if (hDevice.IsInvalid()) 
	{
		DPErrorEx(_FT("Opening %s failed: "), LFSFILT_DEVICE_NAME);
		return FALSE;
	}

	return LfsFiltCtlCreateEventQueue(
		hDevice, 
		LfsEventQueueHandle,
		LfsEventWait);
}


/*++

Close an event queue in LfsFilt

--*/
BOOL WINAPI LfsFiltCtlCloseEventQueue(
		IN HANDLE				hFilter,
		IN LFS_EVTQUEUE_HANDLE	LfsEventQueueHandle
){
	DWORD cbReturned = 0;
	LFS_CLOSEVTQ_PARAM closeEvetqReturn;

	closeEvetqReturn.EventQueueHandle = LfsEventQueueHandle;

	BOOL fSuccess = ::DeviceIoControl(
		hFilter,
		LFS_FILTER_CLOSE_EVTQ,
		&closeEvetqReturn, sizeof(closeEvetqReturn),
		NULL, 0,
		&cbReturned,
		(LPOVERLAPPED) NULL);

	if (!fSuccess) 
	{
		DPErrorEx(_FT("Closing an event queue failed: "));
		return FALSE;
	}

	return TRUE;
}

BOOL WINAPI LfsFiltCtlCloseEventQueue(
		IN LFS_EVTQUEUE_HANDLE	LfsEventQueueHandle)
{
	XTL::AutoFileHandle hDevice = LfsFiltCtlOpenDevice();

	if (hDevice.IsInvalid()) 
	{
		DPErrorEx(_FT("Opening %s failed: "), LFSFILT_DEVICE_NAME);
		return FALSE;
	}

	return LfsFiltCtlCloseEventQueue(
		hDevice, 
		LfsEventQueueHandle);
}


/*++

Get an event header before retrieving the event.

--*/
BOOL WINAPI 
LfsFiltGetEventHeader(
	IN HANDLE				hFilter,
	IN LFS_EVTQUEUE_HANDLE	LfsEventQueueHandle,
	OUT PUINT32				EventLength,
	OUT PUINT32				EventClass)
{
	DWORD cbReturned = 0;
	LFS_GET_EVTHEADER_PARAM		evtHeaderParam;
	LFS_GET_EVTHEADER_RETURN	evtHeaderReturn;

	evtHeaderParam.EventQueueHandle = LfsEventQueueHandle;

	BOOL fSuccess = ::DeviceIoControl(
		hFilter,
		LFS_FILTER_GET_EVTHEADER,
		&evtHeaderParam, sizeof(evtHeaderParam),
		&evtHeaderReturn, sizeof(evtHeaderReturn),
		&cbReturned,
		(LPOVERLAPPED) NULL);

	if (!fSuccess) 
	{
		DPErrorEx(_FT("Closing an event queue failed: "));
		return FALSE;
	}

	if(EventLength) *EventLength = evtHeaderReturn.EventLength;
	if(EventClass) *EventClass = evtHeaderReturn.EventClass;

	return TRUE;
}

BOOL 
WINAPI 
LfsFiltGetEventHeader(
	IN LFS_EVTQUEUE_HANDLE	LfsEventQueueHandle,
	OUT PUINT32				EventLength,
	OUT PUINT32				EventClass)
{
	XTL::AutoFileHandle hDevice = LfsFiltCtlOpenDevice();

	if (hDevice.IsInvalid()) 
	{
		DPErrorEx(_FT("Opening %s failed: "), LFSFILT_DEVICE_NAME);
		return FALSE;
	}

	return LfsFiltGetEventHeader(
		hDevice, 
		LfsEventQueueHandle,
		EventLength,
		EventClass);
}

/*++

retrieve an event

--*/
BOOL 
WINAPI 
LfsFiltGetEvent(
	IN HANDLE				hFilter,
	IN LFS_EVTQUEUE_HANDLE	LfsEventQueueHandle,
	OUT DWORD				EventLength,
	OUT PXEVENT_ITEM		LfsEvent)
{
	DWORD cbReturned = 0;
	LFS_DEQUEUE_EVT_PARAM		dequeueEvtParam;

	dequeueEvtParam.EventQueueHandle = LfsEventQueueHandle;

	BOOL fSuccess = ::DeviceIoControl(
		hFilter,
		LFS_FILTER_DEQUEUE_EVT,
		&dequeueEvtParam, sizeof(dequeueEvtParam),
		LfsEvent, EventLength,
		&cbReturned,
		(LPOVERLAPPED) NULL);

	if (!fSuccess) 
	{
		DPErrorEx(_FT("Closing an event queue failed: "));
		return FALSE;
	}

	return TRUE;

}

BOOL 
WINAPI 
LfsFiltGetEvent(
	IN LFS_EVTQUEUE_HANDLE	LfsEventQueueHandle,
	OUT DWORD				EventLength,
	OUT PXEVENT_ITEM		LfsEvent)
{
	XTL::AutoFileHandle hDevice = LfsFiltCtlOpenDevice();

	if (hDevice.IsInvalid()) 
	{
		DPErrorEx(_FT("Opening %s failed: "), LFSFILT_DEVICE_NAME);
		return FALSE;
	}

	return LfsFiltGetEvent(
		hDevice, 
		LfsEventQueueHandle,
		EventLength,
		LfsEvent);
}

namespace
{
	struct FlaggedValue {
		const UINT32 Value;
		FlaggedValue(UINT32 Value) : Value(Value) {}
		BOOL IsFlagSet(UINT32 Flag) const { 
			return (Flag & Value) == Flag; 
		}
	};
}

/*++

Get NDAS usage stats

--*/
BOOL WINAPI 
LfsFiltQueryNdasUsage(
	IN HANDLE				hFilter,
	IN DWORD				SlotNumber,
	OUT PLFSCTL_NDAS_USAGE	NdasUsage)
{
	DWORD cbReturned = 0;
	LFS_QUERY_NDASUSAGE_PARAM	ndasUsageParam;
	LFS_QUERY_NDASUSAGE_RETURN	ndasUsageReturn;

	ndasUsageParam.SlotNumber = SlotNumber;
	ndasUsageParam.Reserved = 0;

	BOOL fSuccess = ::DeviceIoControl(
		hFilter,
		LFS_FILTER_QUERY_NDASUSAGE,
		&ndasUsageParam, sizeof(ndasUsageParam),
		&ndasUsageReturn, sizeof(ndasUsageReturn),
		&cbReturned,
		(LPOVERLAPPED) NULL);

	if (!fSuccess) 
	{
		DPErrorEx(_FT("LFS_FILTER_QUERY_NDASUSAGE failed: "));
		return FALSE;
	}

	if (NdasUsage) 
	{
		FlaggedValue fv(ndasUsageReturn.NdasUsageFlags);
		NdasUsage->NoDiskVolume = fv.IsFlagSet(LFS_NDASUSAGE_FLAG_NODISKVOL);
		NdasUsage->Attached     = fv.IsFlagSet(LFS_NDASUSAGE_FLAG_ATTACHED);
		NdasUsage->ActPrimary   = fv.IsFlagSet(LFS_NDASUSAGE_FLAG_PRIMARY);
		NdasUsage->ActSecondary = fv.IsFlagSet(LFS_NDASUSAGE_FLAG_SECONDARY);
		NdasUsage->ActReadOnly  = fv.IsFlagSet(LFS_NDASUSAGE_FLAG_READONLY);
		NdasUsage->HasLockedVolume  = fv.IsFlagSet(LFS_NDASUSAGE_FLAG_LOCKED);
		NdasUsage->MountedFSVolumeCount = ndasUsageReturn.MountedFSVolumeCount;
	}

	return TRUE;
}


BOOL WINAPI 
LfsFiltQueryNdasUsage(
	IN DWORD				SlotNumber,
	OUT PLFSCTL_NDAS_USAGE	NdasUsage)
{
	XTL::AutoFileHandle hDevice = LfsFiltCtlOpenDevice();

	if (hDevice.IsInvalid()) 
	{
		DPErrorEx(_FT("Opening %s failed: "), LFSFILT_DEVICE_NAME);
		return FALSE;
	}

	return LfsFiltQueryNdasUsage(
		hDevice, 
		SlotNumber,
		NdasUsage);
}

/*++

Stop a secondary volume

--*/
BOOL WINAPI LfsFiltStopSecondaryVolume(
		IN HANDLE	hFilter,
		IN DWORD	PhysicalDriveNumber
){
	DWORD cbReturned = 0;
	LFS_STOPSECVOLUME_PARAM	stopSecParam;

	stopSecParam.PhysicalDriveNumber = PhysicalDriveNumber;

	BOOL fSuccess = ::DeviceIoControl(
		hFilter,
		LFS_FILTER_STOP_SECVOLUME,
		&stopSecParam, sizeof(stopSecParam),
		NULL, 0,
		&cbReturned,
		(LPOVERLAPPED) NULL);

	if (!fSuccess) 
	{
		DPErrorEx(_FT("Stopping an secondary failed: "));
		return FALSE;
	}

	return TRUE;
}

BOOL WINAPI LfsFiltStopSecondaryVolume(
		IN DWORD	PhysicalDriveNumber
){
	XTL::AutoFileHandle hDevice = LfsFiltCtlOpenDevice();

	if (hDevice.IsInvalid()) 
	{
		DPErrorEx(_FT("Opening %s failed: "), LFSFILT_DEVICE_NAME);
		return FALSE;
	}

	return LfsFiltStopSecondaryVolume(
		hDevice, 
		PhysicalDriveNumber);
}

/*++

Shutdown LfsFilter without a device file handle

--*/
BOOL WINAPI LfsFiltCtlShutdown()
{
	XTL::AutoFileHandle hDevice = LfsFiltCtlOpenDevice();

	if (hDevice.IsInvalid()) 
	{
		DPErrorEx(_FT("Opening %s failed: "), LFSFILT_DEVICE_NAME);
		return FALSE;
	}

	return LfsFiltCtlShutdown(hDevice);
}
