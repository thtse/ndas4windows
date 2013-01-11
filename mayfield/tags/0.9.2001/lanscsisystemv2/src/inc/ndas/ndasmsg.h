/////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2004 XIMETA, Inc.
// All rights reserved.
//
// Module Name:
//
//    _ndasmsg.h
//
// Abstract:
//
//    Messages for Event Logging for the service
//
//
//Notes:
//
//	   DO NOT EDIT THIS FILE BY HAND!
//
//    This file is GENERATED by the xml file.
//    and consequently by MC tool from the _ndasmsg.mc file.
//
//////////////////////////////////////////////////////////////////////////


#ifndef __NDASMSG_H_
#define __NDASMSG_H_

//
//  Values are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//


//
// Define the severity codes
//
#define STATUS_SEVERITY_WARNING          0x2
#define STATUS_SEVERITY_SUCCESS          0x0
#define STATUS_SEVERITY_INFORMATIONAL    0x1
#define STATUS_SEVERITY_ERROR            0x3


//
// MessageId: NDASHLPSVC_ERROR_DEVICE_ENTRY_NOT_FOUND
//
// MessageText:
//
//  Device Entry Not Found.
//
#define NDASHLPSVC_ERROR_DEVICE_ENTRY_NOT_FOUND ((DWORD)0xE0020021L)

//
// MessageId: NDASHLPSVC_ERROR_UNITDEVICE_ENTRY_NOT_FOUND
//
// MessageText:
//
//  Unit Device Entry Not Found.
//
#define NDASHLPSVC_ERROR_UNITDEVICE_ENTRY_NOT_FOUND ((DWORD)0xE0020022L)

//
// MessageId: NDASHLPSVC_ERROR_LOGICALDEVICE_ENTRY_NOT_FOUND
//
// MessageText:
//
//  Logical Device Entry Not Found.
//
#define NDASHLPSVC_ERROR_LOGICALDEVICE_ENTRY_NOT_FOUND ((DWORD)0xE0020023L)

//
// MessageId: NDASHLPSVC_ERROR_CANNOT_UNREGISTER_ENABLED_DEVICE
//
// MessageText:
//
//  Unregistering an enabled device is not permitted.
//
#define NDASHLPSVC_ERROR_CANNOT_UNREGISTER_ENABLED_DEVICE ((DWORD)0xE0020031L)

//
// MessageId: NDASHLPSVC_ERROR_INVALID_SLOT_NUMBER
//
// MessageText:
//
//  Invalid slot number.
//
#define NDASHLPSVC_ERROR_INVALID_SLOT_NUMBER ((DWORD)0xE0020032L)

//
// MessageId: NDASHLPSVC_ERROR_SLOT_ALREADY_OCCUPIED
//
// MessageText:
//
//  Requested slot is used by alother device.
//
#define NDASHLPSVC_ERROR_SLOT_ALREADY_OCCUPIED ((DWORD)0xE0020033L)

//
// MessageId: NDASHLPSVC_ERROR_DUPLICATE_DEVICE_ENTRY
//
// MessageText:
//
//  The requested device already exists.
//
#define NDASHLPSVC_ERROR_DUPLICATE_DEVICE_ENTRY ((DWORD)0xE0020034L)

//
// MessageId: NDASHLPSVC_ERROR_DEVICE_ENTRY_SLOT_FULL
//
// MessageText:
//
//  No more device slot is available.
//
#define NDASHLPSVC_ERROR_DEVICE_ENTRY_SLOT_FULL ((DWORD)0xE0020035L)

//
// MessageId: NDASHLPSVC_ERROR_NDAS_LOGICALDEVICE_NOT_INITIALIZED
//
// MessageText:
//
//  Logical device is not initialized.
//
#define NDASHLPSVC_ERROR_NDAS_LOGICALDEVICE_NOT_INITIALIZED ((DWORD)0xE0020041L)

//
// MessageId: NDASHLPSVC_ERROR_NDAS_LOGICALDEVICE_MEMBER_MISSING
//
// MessageText:
//
//  Some logical device members are missing in the entry.
//
#define NDASHLPSVC_ERROR_NDAS_LOGICALDEVICE_MEMBER_MISSING ((DWORD)0xE0020042L)

//
// MessageId: NDASHLPSVC_ERROR_NDAS_LOGICALDEVICE_NOT_MOUNTED
//
// MessageText:
//
//  Logical device is not mounted.
//
#define NDASHLPSVC_ERROR_NDAS_LOGICALDEVICE_NOT_MOUNTED ((DWORD)0xE0020043L)

//
// MessageId: NDASHLPSVC_ERROR_CONFLICT_LOGICALDEVICE_ENTRY
//
// MessageText:
//
//  Logical device entry is conflicts with existing entries.
//
#define NDASHLPSVC_ERROR_CONFLICT_LOGICALDEVICE_ENTRY ((DWORD)0xE0020044L)

//
// MessageId: NDASHLPSVC_ERROR_DUPLICATE_LOGICALDEVICE_ENTRY
//
// MessageText:
//
//  The requested logical device already exists.
//
#define NDASHLPSVC_ERROR_DUPLICATE_LOGICALDEVICE_ENTRY ((DWORD)0xE0020045L)

//
// MessageId: NDASHLPSVC_ERROR_LOGICALDEVICE_SLOT_FULL
//
// MessageText:
//
//  No more logical device slot is available.
//
#define NDASHLPSVC_ERROR_LOGICALDEVICE_SLOT_FULL ((DWORD)0xE0020046L)

//
// MessageId: NDASHLPSVC_ERROR_UNSUPPORTED_LOGICALDEVICE_TYPE
//
// MessageText:
//
//  Unsupported logical device type.
//
#define NDASHLPSVC_ERROR_UNSUPPORTED_LOGICALDEVICE_TYPE ((DWORD)0xE0020047L)

//
// MessageId: NDASHLPSVC_ERROR_NDAS_LOGICALDEVICE_ACCESS_DENIED
//
// MessageText:
//
//  Granted access for the logical device is insufficent to complete the operation.
//
#define NDASHLPSVC_ERROR_NDAS_LOGICALDEVICE_ACCESS_DENIED ((DWORD)0xE0020050L)

//
// MessageId: NDASHLPSVC_ERROR_NDAS_LOGICALDEVICE_ACCESS_FAILED
//
// MessageText:
//
//  Requested access to the logical device is failed.
//
#define NDASHLPSVC_ERROR_NDAS_LOGICALDEVICE_ACCESS_FAILED ((DWORD)0xE0020051L)

//
// MessageId: NDASHLPSVC_ERROR_COMMAND_VERSION_NOT_SUPPORTED
//
// MessageText:
//
//  Command version is unsupported.
//
#define NDASHLPSVC_ERROR_COMMAND_VERSION_NOT_SUPPORTED ((DWORD)0xE00200E0L)

//
// MessageId: NDASHLPSVC_ERROR_NOT_IMPLEMENTED
//
// MessageText:
//
//  Requested feature is not supported.
//
#define NDASHLPSVC_ERROR_NOT_IMPLEMENTED ((DWORD)0xE00200E1L)

//
// MessageId: NDASHLPSVC_ERROR_ROFILTER_VERSION_MISMATCH
//
// MessageText:
//
//  Unsupported Read-only filter version.
//
#define NDASHLPSVC_ERROR_ROFILTER_VERSION_MISMATCH ((DWORD)0xE00200C0L)

//
// MessageId: NDASUSER_ERROR_SERVICE_CONNECTION_FAILURE
//
// MessageText:
//
//  Communication to the service failed.
//
#define NDASUSER_ERROR_SERVICE_CONNECTION_FAILURE ((DWORD)0xE0010001L)

//
// MessageId: NDASUSER_ERROR_INVALID_DEVICE_STRING_ID_OR_KEY
//
// MessageText:
//
//  Device ID or Key is invalid.
//
#define NDASUSER_ERROR_INVALID_DEVICE_STRING_ID_OR_KEY ((DWORD)0xE0010002L)

//
// MessageId: NDASUSER_ERROR_INVALID_DEVICE_STRING_ID
//
// MessageText:
//
//  Device ID is invalid.
//
#define NDASUSER_ERROR_INVALID_DEVICE_STRING_ID ((DWORD)0xE0010003L)

//
// MessageId: NDASUSER_ERROR_INVALID_DEVICE_STRING_KEY
//
// MessageText:
//
//  Device Key is invalid.
//
#define NDASUSER_ERROR_INVALID_DEVICE_STRING_KEY ((DWORD)0xE0010004L)

//
// MessageId: NDASUSER_ERROR_INVALID_PARAMETER
//
// MessageText:
//
//  Invalid parameter.
//
#define NDASUSER_ERROR_INVALID_PARAMETER ((DWORD)0xE00100FFL)

//
// MessageId: NDASUSER_ERROR_NDAS_LOGICALDEVICE_ACCESS_DENIED
//
// MessageText:
//
//  Logical device access denied.
//
#define NDASUSER_ERROR_NDAS_LOGICALDEVICE_ACCESS_DENIED ((DWORD)0xE0010050L)

//
// MessageId: NDASUSER_ERROR_SERVICE_RETURNED_NOT_IMPLEMENTED
//
// MessageText:
//
//  Service does not support the requested operation.
//
#define NDASUSER_ERROR_SERVICE_RETURNED_NOT_IMPLEMENTED ((DWORD)0xE0010101L)

//
// MessageId: NDASUSER_ERROR_SERVICE_RETURNED_INVALID_REQUEST
//
// MessageText:
//
//  Operation is invalid to the service.
//
#define NDASUSER_ERROR_SERVICE_RETURNED_INVALID_REQUEST ((DWORD)0xE0010102L)

//
// MessageId: NDASUSER_ERROR_SERVICE_RETURNED_TERMINATION
//
// MessageText:
//
//  Service is terminating.
//
#define NDASUSER_ERROR_SERVICE_RETURNED_TERMINATION ((DWORD)0xE0010103L)

//
// MessageId: NDASUSER_ERROR_SERVICE_RETURNED_UNSUPPORTED_VERSION
//
// MessageText:
//
//  Unsupported service version.
//
#define NDASUSER_ERROR_SERVICE_RETURNED_UNSUPPORTED_VERSION ((DWORD)0xE0010104L)

//
// MessageId: NDASUSER_ERROR_EVENT_VERSION_MISMATCH
//
// MessageText:
//
//  Unsupport service event version.
//
#define NDASUSER_ERROR_EVENT_VERSION_MISMATCH ((DWORD)0xE0010200L)

//
// MessageId: NDASUSER_ERROR_EVENT_CALLBACK_FULL
//
// MessageText:
//
//  No more event callback is available.
//
#define NDASUSER_ERROR_EVENT_CALLBACK_FULL ((DWORD)0xE0010201L)

//
// MessageId: NDASUSER_ERROR_INVALID_EVENT_CALLBACK_HANDLE
//
// MessageText:
//
//  Invalid event callback handle.
//
#define NDASUSER_ERROR_INVALID_EVENT_CALLBACK_HANDLE ((DWORD)0xE0010202L)

//
// MessageId: NDASUSER_ERROR_NOT_IMPLEMENTED
//
// MessageText:
//
//  Requested feature is not supported.
//
#define NDASUSER_ERROR_NOT_IMPLEMENTED   ((DWORD)0xE00100E1L)

//
// MessageId: NDASDM_ERROR_NON_SCSI_TYPE_DEVICE
//
// MessageText:
//
//  Non-SCSI type device is found.
//
#define NDASDM_ERROR_NON_SCSI_TYPE_DEVICE ((DWORD)0xEF100100L)

//
// MessageId: NDASDM_ERROR_SRB_IO_CONTROL_ERROR
//
// MessageText:
//
//  SRB IO CONTROL Error
//
#define NDASDM_ERROR_SRB_IO_CONTROL_ERROR ((DWORD)0xEF100102L)

#endif /* __NDASMSG_H_ */