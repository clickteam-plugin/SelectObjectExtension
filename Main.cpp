// ============================================================================
//
// This file are where the Conditions/Actions/Expressions are defined.
// You can manually enter these, or use CICK (recommended)
// See the Extension FAQ in this SDK for more info and where to download it
//
// ============================================================================

// Common Include
#include	"common.h"

// Quick memo: content of the eventInformations arrays
// ---------------------------------------------------
// Menu ID
// String ID
// Code
// Flags
// Number_of_parameters
// Parameter_type [Number_of_parameters]
// Parameter_TitleString [Number_of_parameters]

// Definitions of parameters for each condition
short conditionsInfos[]=
		{
		CID_SelectFirst, CID_SelectFirst, 0, EVFLAGS_ALWAYS, 2, PARAM_OBJECT, PARAM_EXPRESSION, CP0ID_SelectFirst, CP1ID_SelectFirst, 
		CID_SelectHighestAltV, CID_SelectHighestAltV, 1, EVFLAGS_ALWAYS, 2, PARAM_OBJECT, PARAM_EXPRESSION, CP0ID_SelectHighestAltV, CP1ID_SelectHighestAltV, 
		CID_SelectLowestAltV, CID_SelectLowestAltV, 2, EVFLAGS_ALWAYS, 2, PARAM_OBJECT, PARAM_EXPRESSION, CP0ID_SelectLowestAltV, CP1ID_SelectLowestAltV, 
		CID_SelectLast, CID_SelectLast, 3, EVFLAGS_ALWAYS, 2, PARAM_OBJECT, PARAM_EXPRESSION, CP0ID_SelectLast, CP1ID_SelectLast, 
		CID_SelectAll, CID_SelectAll, 4, EVFLAGS_ALWAYS, 1, PARAM_OBJECT, CP0ID_SelectAll, 
		CID_SelectFrontmost, CID_SelectFrontmost, 5, EVFLAGS_ALWAYS, 1, PARAM_OBJECT, CP0ID_SelectFrontmost, 
		CID_SelectRearmost, CID_SelectRearmost, 6, EVFLAGS_ALWAYS, 1, PARAM_OBJECT, CP0ID_SelectRearmost, 
//		CID_SelectByZ, CID_SelectByZ, 7, EVFLAGS_ALWAYS, 2, PARAM_OBJECT, PARAM_COMPARAISON, CP0ID_SelectByZ, CP1ID_SelectByZ, 
//		CID_SelectMostRecent, CID_SelectMostRecent, 0, EVFLAGS_ALWAYS, 1, PARAM_OBJECT, CP0ID_SelectMostRecent, 
		CID_DiscardFirst, CID_DiscardFirst, 7, EVFLAGS_ALWAYS, 2, PARAM_OBJECT, PARAM_EXPRESSION, CP0ID_DiscardFirst, CP1ID_DiscardFirst, 
		CID_DiscardLast, CID_DiscardLast, 8, EVFLAGS_ALWAYS, 2, PARAM_OBJECT, PARAM_EXPRESSION, CP0ID_DiscardLast, CP1ID_DiscardLast, 
		CID_CompareSelected, CID_CompareSelected, 9, EVFLAGS_ALWAYS, 2, PARAM_OBJECT, PARAM_COMPARAISON, CP0ID_CompareSelected, CP1ID_CompareSelected, 
//////////
		CID_SelectRandom, CID_SelectRandom, 10, EVFLAGS_ALWAYS, 2, PARAM_OBJECT, PARAM_EXPRESSION, CP0ID_SelectRandom, CP1ID_SelectRandom, 
		CID_DiscardRandom, CID_DiscardRandom, 11, EVFLAGS_ALWAYS, 2, PARAM_OBJECT, PARAM_EXPRESSION, CP0ID_DiscardRandom, CP1ID_DiscardRandom, 
		CID_SelectTiedHighestAltV, CID_SelectTiedHighestAltV, 12, EVFLAGS_ALWAYS, 2, PARAM_OBJECT, PARAM_EXPRESSION, CP0ID_SelectTiedHighestAltV, CP1ID_SelectTiedHighestAltV, 
		CID_SelectTiedLowestAltV, CID_SelectTiedLowestAltV, 13, EVFLAGS_ALWAYS, 2, PARAM_OBJECT, PARAM_EXPRESSION, CP0ID_SelectTiedLowestAltV, CP1ID_SelectTiedLowestAltV, 
//////////
		CID_SelectIndex, CID_SelectIndex, 14, EVFLAGS_ALWAYS, 2, PARAM_OBJECT, PARAM_EXPRESSION, CP0ID_SelectIndex, CP1ID_SelectIndex, 
		};

// Definitions of parameters for each action
short actionsInfos[]=
		{
		0
		};

// Definitions of parameters for each expression
short expressionsInfos[]=
		{
		EID_GetSelectedByName, EID_GetSelectedByName, 0, 0, 1, EXPPARAM_STRING, EP0ID_GetSelectedByName,
		EID_GetSelectedByFixed, EID_GetSelectedByFixed, 1, 0, 1, EXPPARAM_LONG, EP0ID_GetSelectedByFixed,
		EID_GetNameByFixed, EID_GetNameByFixed, 2, EXPFLAG_STRING, 1, EXPPARAM_LONG, EP0ID_GetNameByFixed,
//////////
//		EID_GetHighestAltByName, EID_GetHighestAltByName, 2, 0, 1, EXPPARAM_STRING, EP0ID_GetHighestAltByName,
//		EID_GetHighestAltByFixed, EID_GetHighestAltByFixed, 3, 0, 1, EXPPARAM_LONG, EP0ID_GetHighestAltByFixed,
//		EID_GetLowestAltByName, EID_GetLowestAltByName, 4, 0, 1, EXPPARAM_STRING, EP0ID_GetLowestAltByName,
//		EID_GetLowestAltByFixed, EID_GetLowestAltByFixed, 5, 0, 1, EXPPARAM_LONG, EP0ID_GetLowestAltByFixed,
//		EID_GetZOrderByName, EID_GetZOrderByName, 2, 0, 1, EXPPARAM_STRING, EP0ID_GetZOrderByName,
//		EID_GetZOrderByFixed, EID_GetZOrderByFixed, 3, 0, 1, EXPPARAM_LONG, EP0ID_GetZOrderByFixed,
		};


__inline void SelectAll( const LPRH rhPtr, const LPOIL pObjectInfo )
{
	const LPOBL ObjectList = rhPtr->rhObjectList; //get a pointer to the mmf object list

	pObjectInfo->oilNumOfSelected = pObjectInfo->oilNObjects;
	pObjectInfo->oilListSelected = pObjectInfo->oilObject;
	pObjectInfo->oilEventCount = rhPtr->rh2.rh2EventCount; //tell mmf that the object selection is relevant to this event

	int i = pObjectInfo->oilObject;
	while(i >= 0)
	{
		headerObject* pObject = ObjectList[i].oblOffset;
		pObject->hoNextSelected = pObject->hoOiNext;
		i = pObject->hoOiNext;
	}
}

__inline void SelectAll( const LPRH rhPtr, short Oi )
{
	const LPOIL OiList = rhPtr->rhOiList; //get a pointer to the mmf object info list

	const LPOIL pObjectInfo = GetOILPtr(OiList, Oi);
	SelectAll(rhPtr, pObjectInfo);
}

__inline void SelectNone( const LPRH rhPtr, const LPOIL pObjectInfo )
{
	pObjectInfo->oilNumOfSelected = 0;
	pObjectInfo->oilListSelected = -1;
	pObjectInfo->oilEventCount = rhPtr->rh2.rh2EventCount; //tell mmf that the object selection is relevant to this event
}

__inline void SelectNone( const LPRH rhPtr, short Oi )
{
	const LPOIL OiList = rhPtr->rhOiList; //get a pointer to the mmf object info list

	const LPOIL pObjectInfo = GetOILPtr(OiList, Oi);
	SelectNone(rhPtr, pObjectInfo);
}


// ============================================================================
//
// CONDITION ROUTINES
// 
// ============================================================================

// -----------------
// Select First/Last( )
// -----------------
// Selects the first/last p2 selected objects of type p1
// 

long WINAPI DLLExport CND_SelectFirst(LPRDATA rdPtr, long param1, long param2)
{
	short p1 = ((eventParam*)param1)->evp.evpW.evpW0;
	short p2 = (short)param2;

	if(p2<=0) // invalid count
		return false;

	const LPRH rhPtr = rdPtr->rHo.hoAdRunHeader; //get a pointer to the mmf runtime header
	const LPOBL ObjectList = rhPtr->rhObjectList; //get a pointer to the mmf object list
	const LPOIL OiList = rhPtr->rhOiList; //get a pointer to the mmf object info list
	const LPQOI QualToOiList = rhPtr->rhQualToOiList; //get a pointer to the mmf qualifier to Oi list

	if(p1 & 0x8000) // dealing with a qualifier...
	{
		// For qualifiers evpW0( & 0x7FFF ) is the offset in the qualToOi array
		// And evpW1( & 0x7FFF ) is the qualifier number.
		LPQOI CurrentQualToOiStart = PtrAddBytes(QualToOiList, p1 & 0x7FFF);
		LPQOI CurrentQualToOi = CurrentQualToOiStart;

		int numSelected = 0;

		// Loop through all objects associated with this qualifier
		for (CurrentQualToOi;
			CurrentQualToOi->qoiOiList >= 0 && p2 - numSelected > 0;
			CurrentQualToOi = PtrAddBytes(CurrentQualToOi, 4) )
		{
			LPOIL CurrentOi = GetOILPtr(OiList, CurrentQualToOi->qoiOiList); //get a pointer to the objectInfo
			if(CurrentOi->oilNObjects <= 0) //skip if there are none of the object
				continue;

			bool prevSelected = (CurrentOi->oilEventCount == rhPtr->rh2.rh2EventCount); //find out if conditions have selected any param1's yet
			if(prevSelected && CurrentOi->oilNumOfSelected <= 0) //if it thinks there are but there's 0 (??) then skip
				continue;

			if(!prevSelected && CurrentOi->oilNObjects <= p2 - numSelected) //skip if there are less of the object than they want
			{
				numSelected += CurrentOi->oilNObjects;
				SelectAll( rhPtr, CurrentQualToOi->qoiOiList );
				continue;
			}

			if(prevSelected && CurrentOi->oilNumOfSelected <= p2 - numSelected) //skip if there are less of the object than they want
			{
				numSelected += CurrentOi->oilNumOfSelected;
				continue;
			}

			// There are more of this object than asked for, so tidy up and return
			if(!prevSelected)
			{
				CurrentOi->oilEventCount = rhPtr->rh2.rh2EventCount; //tell mmf that the object selection is relevant to this event
				CurrentOi->oilListSelected = CurrentOi->oilObject; //select the first object if it hasn't been done already
				headerObject* CurrentObject = ObjectList[CurrentOi->oilObject].oblOffset;
				for(int i = p2 - numSelected - 1; i>0; i--)
				{
					CurrentObject->hoNextSelected = CurrentObject->hoOiNext;
					if(CurrentObject->hoOiNext < 0)
						break;
					else
						CurrentObject = ObjectList[CurrentObject->hoOiNext].oblOffset;
				}
				CurrentObject->hoNextSelected = -1;
			}
			else
			{
				headerObject* CurrentObject = ObjectList[CurrentOi->oilListSelected].oblOffset;
				for(int i = p2 - numSelected - 1; i>0; i--)
				{
					if(CurrentObject->hoNextSelected < 0)
						break;
					else
						CurrentObject = ObjectList[CurrentObject->hoNextSelected].oblOffset;
				}
				CurrentObject->hoNextSelected = -1;
			}

			CurrentOi->oilNumOfSelected = p2 - numSelected;

			break;
		}

		if (CurrentQualToOi->qoiOiList >= 0)
			CurrentQualToOi = PtrAddBytes(CurrentQualToOi, 4);

		for (CurrentQualToOi;
			CurrentQualToOi->qoiOiList >= 0;
			CurrentQualToOi = PtrAddBytes(CurrentQualToOi, 4) )
		{
			LPOIL CurrentOi = GetOILPtr(OiList, CurrentQualToOi->qoiOiList); //get a pointer to the objectInfo
			if(CurrentOi->oilNObjects <= 0) //skip if there are none of the object
				continue;

			SelectNone( rhPtr, CurrentQualToOi->qoiOiList );
		}

		return (numSelected > 0);
	}
	else
	{
		LPOIL CurrentOi = GetOILPtr(OiList, p1); //get a pointer to the objectInfo for param1
		if(CurrentOi->oilNObjects <= 0) //return if there are none of the object
			return false;
		if(CurrentOi->oilNObjects <= p2) //return if there are less of the object than they want
		{
			SelectAll( rhPtr, p1 );
			return true;
		}

		bool prevSelected = (CurrentOi->oilEventCount == rhPtr->rh2.rh2EventCount); //find out if conditions have selected any param1's yet
		if(prevSelected && CurrentOi->oilNumOfSelected <= 0) //if it thinks there are but there's 0 (??) then return
			return false;
		if(prevSelected && CurrentOi->oilNumOfSelected <= p2) //return if there are less of the object selected than they want
			return true;

		CurrentOi->oilEventCount = rhPtr->rh2.rh2EventCount; //tell mmf that our condition selects objects for this event
		if(!prevSelected)
		{	//apparently in mmf2 oilObject always points to the most recently created, not the highest index
			CurrentOi->oilListSelected = CurrentOi->oilObject; //select the first object if it hasn't been done already
			headerObject* CurrentObject = ObjectList[CurrentOi->oilObject].oblOffset;
			for(int i = p2 - 1; i>0; i--)
			{
				CurrentObject->hoNextSelected = CurrentObject->hoOiNext;
				if(CurrentObject->hoOiNext < 0)
					break;
				else
					CurrentObject = ObjectList[CurrentObject->hoOiNext].oblOffset;
			}
			CurrentObject->hoNextSelected = -1;
		}
		else
		{
			headerObject* CurrentObject = ObjectList[CurrentOi->oilListSelected].oblOffset;
			for(int i = p2 - 1; i>0; i--)
			{
				if(CurrentObject->hoNextSelected < 0)
					break;
				else
					CurrentObject = ObjectList[CurrentObject->hoNextSelected].oblOffset;
			}
			CurrentObject->hoNextSelected = -1;
		}

		CurrentOi->oilNumOfSelected = p2;

		return true;
	}
}

long WINAPI DLLExport CND_SelectLast(LPRDATA rdPtr, long param1, long param2)
{
	short p1 = ((eventParam*)param1)->evp.evpW.evpW0;
	short p2 = (short)param2;

	if(p2<=0) // invalid count
		return false;

	const LPRH rhPtr = rdPtr->rHo.hoAdRunHeader; //get a pointer to the mmf runtime header
	const LPOBL ObjectList = rhPtr->rhObjectList; //get a pointer to the mmf object list
	const LPOIL OiList = rhPtr->rhOiList; //get a pointer to the mmf object info list
	const LPQOI QualToOiList = rhPtr->rhQualToOiList; //get a pointer to the mmf qualifier to Oi list

	if(p1 & 0x8000) // dealing with a qualifier...
	{
		// For qualifiers evpW0( & 0x7FFF ) is the offset in the qualToOi array
		// And evpW1( & 0x7FFF ) is the qualifier number.
		LPQOI CurrentQualToOiStart = PtrAddBytes(QualToOiList, p1 & 0x7FFF);

		int numSelected = 0;
		// Loop through all objects associated with this qualifier
		for (LPQOI CurrentQualToOi = CurrentQualToOiStart;
			CurrentQualToOi->qoiOiList >= 0;
			CurrentQualToOi = PtrAddBytes(CurrentQualToOi, 4) )
		{
			LPOIL CurrentOi = GetOILPtr(OiList, CurrentQualToOi->qoiOiList); //get a pointer to the objectInfo
			if(CurrentOi->oilNObjects <= 0) //skip if there are none of the object
				continue;

			bool prevSelected = (CurrentOi->oilEventCount == rhPtr->rh2.rh2EventCount);
			if(prevSelected && CurrentOi->oilNumOfSelected <= 0) //if it thinks there are but there's 0 (??) then skip
				continue;

			if(prevSelected)
				numSelected += CurrentOi->oilNumOfSelected;
			else
				numSelected += CurrentOi->oilNObjects;
		}

		if (numSelected <= p2) //return if there are less of the object than they want
		{
			// Loop through all objects associated with this qualifier
			for (LPQOI CurrentQualToOi = CurrentQualToOiStart;
				CurrentQualToOi->qoiOiList >= 0;
				CurrentQualToOi = PtrAddBytes(CurrentQualToOi, 4) )
			{
				LPOIL CurrentOi = GetOILPtr(OiList, CurrentQualToOi->qoiOiList); //get a pointer to the objectInfo
				if(CurrentOi->oilNObjects <= 0) //skip if there are none of the object
					continue;

				bool prevSelected = (CurrentOi->oilEventCount == rhPtr->rh2.rh2EventCount);
				if (!prevSelected)
					SelectAll( rhPtr, CurrentOi );
			}
			return true;
		}

		int numToDiscard = numSelected - p2;
		int numDiscarded = 0;
		LPQOI CurrentQualToOi = CurrentQualToOiStart;
		// Loop through all objects associated with this qualifier
		for (CurrentQualToOi;
			CurrentQualToOi->qoiOiList >= 0 && numDiscarded < numToDiscard;
			CurrentQualToOi = PtrAddBytes(CurrentQualToOi, 4) )
		{
			LPOIL CurrentOi = GetOILPtr(OiList, CurrentQualToOi->qoiOiList); //get a pointer to the objectInfo
			if(CurrentOi->oilNObjects <= 0) //skip if there are none of the object
				continue;

			bool prevSelected = (CurrentOi->oilEventCount == rhPtr->rh2.rh2EventCount); //find out if conditions have selected any param1's yet
			if(prevSelected && CurrentOi->oilNumOfSelected <= 0) //if it thinks there are but there's 0 (??) then skip
				continue;

			if(!prevSelected && CurrentOi->oilNObjects <= numToDiscard - numDiscarded) //skip if there are less of the object than they want
			{
				numDiscarded += CurrentOi->oilNObjects;
				SelectNone( rhPtr, CurrentQualToOi->qoiOiList );
				continue;
			}

			if(prevSelected && CurrentOi->oilNumOfSelected <= numToDiscard - numDiscarded) //skip if there are less of the object than they want
			{
				numDiscarded += CurrentOi->oilNumOfSelected;
				SelectNone( rhPtr, CurrentQualToOi->qoiOiList );
				continue;
			}

			// There are more of this object than asked for, so tidy up and return
			if(!prevSelected)
			{
				CurrentOi->oilEventCount = rhPtr->rh2.rh2EventCount; //tell mmf that the object selection is relevant to this event
				headerObject* CurrentObject = ObjectList[CurrentOi->oilObject].oblOffset;

				for(int i = numToDiscard - numDiscarded; i>0; i--)
				{
					if(CurrentObject->hoOiNext < 0)
						break; // error?
					else
						CurrentObject = ObjectList[CurrentObject->hoOiNext].oblOffset;
				}
				CurrentOi->oilListSelected = CurrentObject->hoNumber;
				CurrentOi->oilNumOfSelected = CurrentOi->oilNObjects - (numToDiscard - numDiscarded);
				for(int i = CurrentOi->oilNObjects - (numToDiscard - numDiscarded); i>0; i--)
				{
					CurrentObject->hoNextSelected = CurrentObject->hoOiNext;
					if(CurrentObject->hoOiNext < 0)
						break; // error?
					else
						CurrentObject = ObjectList[CurrentObject->hoOiNext].oblOffset;
				}
			}
			else
			{
				headerObject* CurrentObject = ObjectList[CurrentOi->oilListSelected].oblOffset;
				for(int i = CurrentOi->oilNumOfSelected - (numToDiscard - numDiscarded); i>0; i--)
				{
					if(CurrentObject->hoNextSelected < 0)
						break; // error?
					else
						CurrentObject = ObjectList[CurrentObject->hoNextSelected].oblOffset;
				}
				CurrentOi->oilListSelected = CurrentObject->hoNumber;
				CurrentOi->oilNumOfSelected = CurrentOi->oilNumOfSelected - (numToDiscard - numDiscarded);
			}

			break;
		}

		if (CurrentQualToOi->qoiOiList >= 0)
			CurrentQualToOi = PtrAddBytes(CurrentQualToOi, 4);

		for (CurrentQualToOi;
			CurrentQualToOi->qoiOiList >= 0;
			CurrentQualToOi = PtrAddBytes(CurrentQualToOi, 4) )
		{
			LPOIL CurrentOi = GetOILPtr(OiList, CurrentQualToOi->qoiOiList); //get a pointer to the objectInfo
			if(CurrentOi->oilNObjects <= 0) //skip if there are none of the object
				continue;

			bool prevSelected = (CurrentOi->oilEventCount == rhPtr->rh2.rh2EventCount);
			if (!prevSelected)
				SelectAll( rhPtr, CurrentOi );
		}

		return true;
	}
	else
	{
		LPOIL CurrentOi = GetOILPtr(OiList, p1); //get a pointer to the objectInfo for param1
		if(CurrentOi->oilNObjects <= 0) //return if there are none of the object
			return false;
		if(CurrentOi->oilNObjects <= p2) //return if there are less of the object than they want
		{
			SelectAll( rhPtr, p1 );
			return true;
		}

		bool prevSelected = (CurrentOi->oilEventCount == rhPtr->rh2.rh2EventCount); //find out if conditions have selected any param1's yet
		if(prevSelected && CurrentOi->oilNumOfSelected <= 0) //if it thinks there are but there's 0 (??) then return
			return false;
		if(prevSelected && CurrentOi->oilNumOfSelected <= p2) //return if there are less of the object selected than they want
			return true;

		CurrentOi->oilEventCount = rhPtr->rh2.rh2EventCount; //tell mmf that our condition selects objects for this event
		if(!prevSelected)
		{
			headerObject* CurrentObject = ObjectList[CurrentOi->oilObject].oblOffset;
			for(int i = CurrentOi->oilNObjects - p2; i>0; i--)
			{
				if(CurrentObject->hoOiNext < 0)
					break; //shouldn't happen but it helps to be safe
				CurrentObject = ObjectList[CurrentObject->hoOiNext].oblOffset;
			}
			CurrentOi->oilListSelected = CurrentObject->hoNumber; //set selection start point
			for(int i = p2 - 1; i>0; i--)
			{
				CurrentObject->hoNextSelected = CurrentObject->hoOiNext;
				if(CurrentObject->hoOiNext < 0)
					break;
				CurrentObject = ObjectList[CurrentObject->hoOiNext].oblOffset;
			}
			CurrentObject->hoNextSelected = -1;
		}
		else
		{
			headerObject* CurrentObject = ObjectList[CurrentOi->oilListSelected].oblOffset;
			for(int i = CurrentOi->oilNumOfSelected - p2; i>0; i--)
			{
				if(CurrentObject->hoNextSelected < 0)
					break;
				CurrentObject = ObjectList[CurrentObject->hoNextSelected].oblOffset;
			}
			CurrentOi->oilListSelected = CurrentObject->hoNumber; //set selection start point
			//we don't set the end to -1, because we're not moving the end of the selection
		}

		CurrentOi->oilNumOfSelected = p2;

		return true;
	}
}

// -----------------
// Discard First/Last( )
// -----------------
// Discards the first/last p2 selected objects of type p1
// 

long WINAPI DLLExport CND_DiscardFirst(LPRDATA rdPtr, long param1, long param2)
{
	short p1 = ((eventParam*)param1)->evp.evpW.evpW0;
	short p2 = (short)param2;

	if(p2<=0) // invalid count
		return false;

	const LPRH rhPtr = rdPtr->rHo.hoAdRunHeader; //get a pointer to the mmf runtime header
	const LPOBL ObjectList = rhPtr->rhObjectList; //get a pointer to the mmf object list
	const LPOIL OiList = rhPtr->rhOiList; //get a pointer to the mmf object info list
	const LPQOI QualToOiList = rhPtr->rhQualToOiList; //get a pointer to the mmf qualifier to Oi list

	if(p1 & 0x8000) // dealing with a qualifier...
	{
		// For qualifiers evpW0( & 0x7FFF ) is the offset in the qualToOi array
		// And evpW1( & 0x7FFF ) is the qualifier number.
		LPQOI CurrentQualToOiStart = PtrAddBytes(QualToOiList, p1 & 0x7FFF);
		LPQOI CurrentQualToOi = CurrentQualToOiStart;

		int numDiscarded = 0;

		// Loop through all objects associated with this qualifier
		for (CurrentQualToOi;
			CurrentQualToOi->qoiOiList >= 0 && p2 - numDiscarded > 0;
			CurrentQualToOi = PtrAddBytes(CurrentQualToOi, 4) )
		{
			LPOIL CurrentOi = GetOILPtr(OiList, CurrentQualToOi->qoiOiList); //get a pointer to the objectInfo
			if(CurrentOi->oilNObjects <= 0) //skip if there are none of the object
				continue;

			bool prevSelected = (CurrentOi->oilEventCount == rhPtr->rh2.rh2EventCount); //find out if conditions have selected any param1's yet
			if(prevSelected && CurrentOi->oilNumOfSelected <= 0) //if it thinks there are but there's 0 (??) then skip
				continue;

			if(!prevSelected && CurrentOi->oilNObjects <= p2 - numDiscarded) //skip if there are less of the object than they want
			{
				numDiscarded += CurrentOi->oilNObjects;
				SelectNone( rhPtr, CurrentQualToOi->qoiOiList );
				continue;
			}

			if(prevSelected && CurrentOi->oilNumOfSelected <= p2 - numDiscarded) //skip if there are less of the object than they want
			{
				numDiscarded += CurrentOi->oilNumOfSelected;
				SelectNone( rhPtr, CurrentQualToOi->qoiOiList );
				continue;
			}

			// There are more of this object than asked for, so tidy up and return
			if(!prevSelected)
			{
				CurrentOi->oilEventCount = rhPtr->rh2.rh2EventCount; //tell mmf that the object selection is relevant to this event
				headerObject* CurrentObject = ObjectList[CurrentOi->oilObject].oblOffset;

				for(int i = p2 - numDiscarded; i>0; i--)
				{
					if(CurrentObject->hoOiNext < 0)
						break; // error?
					else
						CurrentObject = ObjectList[CurrentObject->hoOiNext].oblOffset;
				}
				CurrentOi->oilListSelected = CurrentObject->hoNumber; //select the first object if it hasn't been done already
				CurrentOi->oilNumOfSelected = CurrentOi->oilNObjects - (p2 - numDiscarded);
				for(int i = CurrentOi->oilNObjects - (p2 - numDiscarded); i>0; i--)
				{
					CurrentObject->hoNextSelected = CurrentObject->hoOiNext;
					if(CurrentObject->hoOiNext < 0)
						break; // error?
					else
						CurrentObject = ObjectList[CurrentObject->hoOiNext].oblOffset;
				}
			}
			else
			{
				headerObject* CurrentObject = ObjectList[CurrentOi->oilListSelected].oblOffset;
				for(int i = CurrentOi->oilNumOfSelected - (p2 - numDiscarded); i>0; i--)
				{
					if(CurrentObject->hoNextSelected < 0)
						break;
					else
						CurrentObject = ObjectList[CurrentObject->hoNextSelected].oblOffset;
				}
				CurrentOi->oilListSelected = CurrentObject->hoNumber;
				CurrentOi->oilNumOfSelected = CurrentOi->oilNumOfSelected - (p2 - numDiscarded);
			}

			break;
		}

		if (CurrentQualToOi->qoiOiList >= 0)
			CurrentQualToOi = PtrAddBytes(CurrentQualToOi, 4);

		for (CurrentQualToOi;
			CurrentQualToOi->qoiOiList >= 0;
			CurrentQualToOi = PtrAddBytes(CurrentQualToOi, 4) )
		{
			LPOIL CurrentOi = GetOILPtr(OiList, CurrentQualToOi->qoiOiList); //get a pointer to the objectInfo
			if(CurrentOi->oilNObjects <= 0) //skip if there are none of the object
				continue;

			bool prevSelected = (CurrentOi->oilEventCount == rhPtr->rh2.rh2EventCount);
			if (!prevSelected)
				SelectAll( rhPtr, CurrentOi );
		}

		return true;
	}
	else
	{
		LPOIL CurrentOi = GetOILPtr(OiList, p1); //get a pointer to the objectInfo for param1
		if(CurrentOi->oilNObjects <= 0) //return if there are none of the object
			return false;
		if(CurrentOi->oilNObjects <= p2) //return if there are less of the object than they want
			return false;

		bool prevSelected = (CurrentOi->oilEventCount == rhPtr->rh2.rh2EventCount); //find out if conditions have selected any param1's yet
		if(prevSelected && CurrentOi->oilNumOfSelected <= 0) //if it thinks there are but there's 0 (??) then return
			return false;
		if(prevSelected && CurrentOi->oilNumOfSelected <= p2) //return if there are less of the object selected than they want
			return false;

		CurrentOi->oilEventCount = rhPtr->rh2.rh2EventCount; //tell mmf that our condition selects objects for this event
		if(!prevSelected)
		{	//apparently in mmf2 oilObject always points to the most recently created, not the highest index
			headerObject* CurrentObject = ObjectList[CurrentOi->oilObject].oblOffset;
			for(int i = p2; i>0; i--)
			{
				if(CurrentObject->hoOiNext < 0)
					break;
				else
					CurrentObject = ObjectList[CurrentObject->hoOiNext].oblOffset;
			}
			CurrentOi->oilListSelected = CurrentObject->hoNumber; //select the new first object
			for(int i = CurrentOi->oilNObjects - p2 - 1; i>0; i--)
			{
				CurrentObject->hoNextSelected = CurrentObject->hoOiNext;
				if(CurrentObject->hoOiNext < 0)
					break;
				CurrentObject = ObjectList[CurrentObject->hoOiNext].oblOffset;
			}
			CurrentObject->hoNextSelected = -1;
			CurrentOi->oilNumOfSelected = CurrentOi->oilNObjects - p2;
		}
		else
		{
			headerObject* CurrentObject = ObjectList[CurrentOi->oilListSelected].oblOffset;
			for(int i = p2; i>0; i--)
			{
				if(CurrentObject->hoNextSelected < 0)
					break;
				else
					CurrentObject = ObjectList[CurrentObject->hoNextSelected].oblOffset;
			}
			CurrentOi->oilListSelected = CurrentObject->hoNumber; //select the new first object
			CurrentOi->oilNumOfSelected -= p2;
		}

		return true;
	}
}

long WINAPI DLLExport CND_DiscardLast(LPRDATA rdPtr, long param1, long param2)
{
	short p1 = ((eventParam*)param1)->evp.evpW.evpW0;
	short p2 = (short)param2;

	if(p1<0) // dealing with a qualifier...
		return false;

	const LPRH rhPtr = rdPtr->rHo.hoAdRunHeader; //get a pointer to the mmf runtime header
	const LPOBL ObjectList = rhPtr->rhObjectList; //get a pointer to the mmf object list
	const LPOIL OiList = rhPtr->rhOiList; //get a pointer to the mmf object info list

	LPOIL CurrentOi = GetOILPtr(OiList, p1); //get a pointer to the objectInfo for param1
	if(CurrentOi->oilNObjects <= 0) //return if there are none of the object
		return false;
	if(CurrentOi->oilNObjects <= p2) //return if there are less of the object than they want
		return false;

	bool prevSelected = (CurrentOi->oilEventCount == rhPtr->rh2.rh2EventCount); //find out if conditions have selected any param1's yet
	if(prevSelected && CurrentOi->oilNumOfSelected <= 0) //if it thinks there are but there's 0 (??) then return
		return false;
	if(prevSelected && CurrentOi->oilNumOfSelected <= p2) //return if there are less of the object selected than they want
		return false;

	CurrentOi->oilEventCount = rhPtr->rh2.rh2EventCount; //tell mmf that our condition selects objects for this event
	if(!prevSelected)
	{
		CurrentOi->oilListSelected = CurrentOi->oilObject; //select the first object if it hasn't been done already
		headerObject* CurrentObject = ObjectList[CurrentOi->oilObject].oblOffset;
        for(int i = CurrentOi->oilNObjects - p2 - 1; i>0; i--)
		{
			CurrentObject->hoNextSelected = CurrentObject->hoOiNext;
			if(CurrentObject->hoOiNext < 0)
				break;
			else
				CurrentObject = ObjectList[CurrentObject->hoOiNext].oblOffset;
		}
		CurrentObject->hoNextSelected = -1;
		CurrentOi->oilNumOfSelected = CurrentOi->oilNObjects - p2;
	}
	else
	{
		headerObject* CurrentObject = ObjectList[CurrentOi->oilListSelected].oblOffset;
        for(int i = CurrentOi->oilNObjects - p2 - 1; i>0; i--)
		{
			if(CurrentObject->hoNextSelected < 0)
				break;
			else
				CurrentObject = ObjectList[CurrentObject->hoNextSelected].oblOffset;
		}
		CurrentObject->hoNextSelected = -1;
		CurrentOi->oilNumOfSelected -= p2;
	}

	return true;
}

// -----------------
// Select at Index( )
// -----------------
// Selects the object of type p1 at index p2
// 

long WINAPI DLLExport CND_SelectIndex(LPRDATA rdPtr, long param1, long param2)
{
	short p1 = ((eventParam*)param1)->evp.evpW.evpW0;
	short p2 = (short)param2;

	if(p2<0) // invalid index
		return false;

	const LPRH rhPtr = rdPtr->rHo.hoAdRunHeader; //get a pointer to the mmf runtime header
	const LPOBL ObjectList = rhPtr->rhObjectList; //get a pointer to the mmf object list
	const LPOIL OiList = rhPtr->rhOiList; //get a pointer to the mmf object info list
	const LPQOI QualToOiList = rhPtr->rhQualToOiList; //get a pointer to the mmf qualifier to Oi list

	if(p1 & 0x8000) // dealing with a qualifier...
	{
		// For qualifiers evpW0( & 0x7FFF ) is the offset in the qualToOi array
		// And evpW1( & 0x7FFF ) is the qualifier number.
		LPQOI CurrentQualToOiStart = PtrAddBytes(QualToOiList, p1 & 0x7FFF);
		LPQOI CurrentQualToOi = CurrentQualToOiStart;

		int numSkipped = 0;
		int numSelected = 0;

		// Loop through all objects associated with this qualifier
		for (CurrentQualToOi;
			CurrentQualToOi->qoiOiList >= 0 && p2 - numSkipped >= 0;
			CurrentQualToOi = PtrAddBytes(CurrentQualToOi, 4) )
		{
			LPOIL CurrentOi = GetOILPtr(OiList, CurrentQualToOi->qoiOiList); //get a pointer to the objectInfo
			if(CurrentOi->oilNObjects <= 0) //skip if there are none of the object
				continue;

			bool prevSelected = (CurrentOi->oilEventCount == rhPtr->rh2.rh2EventCount); //find out if conditions have selected any param1's yet
			if(prevSelected && CurrentOi->oilNumOfSelected <= 0) //if it thinks there are but there's 0 (??) then skip
				continue;

			if(!prevSelected && CurrentOi->oilNObjects <= p2 - numSkipped) //skip if there are less of the object than they want
			{
				SelectNone( rhPtr, CurrentQualToOi->qoiOiList );
				numSkipped += CurrentOi->oilNObjects;
				continue;
			}

			if(prevSelected && CurrentOi->oilNumOfSelected <= p2 - numSkipped) //skip if there are less of the object than they want
			{
				SelectNone( rhPtr, CurrentQualToOi->qoiOiList );
				numSkipped += CurrentOi->oilNumOfSelected;
				continue;
			}

			// There are less of this object than asked for, so tidy up and return
			if(!prevSelected)
			{
				headerObject* CurrentObject = ObjectList[CurrentOi->oilObject].oblOffset;
				for(int i = p2 - numSkipped; i>0; i--)
				{
					if(CurrentObject->hoOiNext < 0)
						break; //shouldn't happen but it helps to be safe
					CurrentObject = ObjectList[CurrentObject->hoOiNext].oblOffset;
				}
				CurrentOi->oilEventCount = rhPtr->rh2.rh2EventCount; //tell mmf that our condition selects objects for this event
				CurrentOi->oilListSelected = CurrentObject->hoNumber; //set selection start point
				CurrentOi->oilNumOfSelected = 1;
				CurrentObject->hoNextSelected = -1;
			}
			else
			{
				headerObject* CurrentObject = ObjectList[CurrentOi->oilListSelected].oblOffset;
				for(int i = p2 - numSkipped; i>0; i--)
				{
					if(CurrentObject->hoNextSelected < 0)
						break;
					CurrentObject = ObjectList[CurrentObject->hoNextSelected].oblOffset;
				}
				CurrentOi->oilListSelected = CurrentObject->hoNumber; //set selection start point
				CurrentOi->oilNumOfSelected = 1;
				CurrentObject->hoNextSelected = -1;
			}
			numSelected = 1;

			break;
		}

		if (CurrentQualToOi->qoiOiList >= 0)
			CurrentQualToOi = PtrAddBytes(CurrentQualToOi, 4);

		for (CurrentQualToOi;
			CurrentQualToOi->qoiOiList >= 0;
			CurrentQualToOi = PtrAddBytes(CurrentQualToOi, 4) )
		{
			LPOIL CurrentOi = GetOILPtr(OiList, CurrentQualToOi->qoiOiList); //get a pointer to the objectInfo
			if(CurrentOi->oilNObjects <= 0) //skip if there are none of the object
				continue;

			SelectNone( rhPtr, CurrentQualToOi->qoiOiList );
		}

		return (numSelected > 0);
	}
	else
	{
		LPOIL CurrentOi = GetOILPtr(OiList, p1); //get a pointer to the objectInfo for param1
		if(CurrentOi->oilNObjects <= 0) //return if there are none of the object
			return false;
		if(CurrentOi->oilNObjects <= p2) //return if there are less of the object than they want
			return false;

		bool prevSelected = (CurrentOi->oilEventCount == rhPtr->rh2.rh2EventCount); //find out if conditions have selected any param1's yet
		if(prevSelected && CurrentOi->oilNumOfSelected <= 0) //if it thinks there are but there's 0 (??) then return
			return false;
		if(prevSelected && CurrentOi->oilNumOfSelected <= p2) //return if there are less of the object selected than they want
			return false;

		if(!prevSelected)
		{
			headerObject* CurrentObject = ObjectList[CurrentOi->oilObject].oblOffset;
			for(int i = p2; i>0; i--)
			{
				if(CurrentObject->hoOiNext < 0)
					break; //shouldn't happen but it helps to be safe
				CurrentObject = ObjectList[CurrentObject->hoOiNext].oblOffset;
			}
			CurrentOi->oilEventCount = rhPtr->rh2.rh2EventCount; //tell mmf that our condition selects objects for this event
			CurrentOi->oilListSelected = CurrentObject->hoNumber; //set selection start point
			CurrentOi->oilNumOfSelected = 1;
			CurrentObject->hoNextSelected = -1;
		}
		else
		{
			headerObject* CurrentObject = ObjectList[CurrentOi->oilListSelected].oblOffset;
			for(int i = p2; i>0; i--)
			{
				if(CurrentObject->hoNextSelected < 0)
					break;
				CurrentObject = ObjectList[CurrentObject->hoNextSelected].oblOffset;
			}
			CurrentOi->oilListSelected = CurrentObject->hoNumber; //set selection start point
			CurrentOi->oilNumOfSelected = 1;
			CurrentObject->hoNextSelected = -1;
		}

		return true;
	}
}

// -----------------
// Select/Discard Random( )
// -----------------
// Selects/Discards p2 random selected objects of type p1
// 

//long WINAPI DLLExport CND_SelectRandom(LPRDATA rdPtr, long param1, long param2)
//{
//	short p1 = ((eventParam*)param1)->evp.evpW.evpW0;
//	short p2 = (short)param2;
//
//	if(p1<0) // dealing with a qualifier...
//		return false;
//
//	return false;
//}
//
//long WINAPI DLLExport CND_DiscardRandom(LPRDATA rdPtr, long param1, long param2)
//{
//	short p1 = ((eventParam*)param1)->evp.evpW.evpW0;
//	short p2 = (short)param2;
//
//	if(p1<0) // dealing with a qualifier...
//		return false;
//
//	return false;
//}

// -----------------
// Re-select all( )
// -----------------
// Selects all objects of type p1 (regardless of current selection)
// 

long WINAPI DLLExport CND_SelectAll(LPRDATA rdPtr, long param1, long param2)
{
	short p1 = ((eventParam*)param1)->evp.evpW.evpW0;

	const LPRH rhPtr = rdPtr->rHo.hoAdRunHeader; //get a pointer to the mmf runtime header
	const LPOIL OiList = rhPtr->rhOiList; //get a pointer to the mmf object info list
	const LPQOI QualToOiList = rhPtr->rhQualToOiList; //get a pointer to the mmf qualifier to Oi list

	if(p1 & 0x8000) // dealing with a qualifier...
	{
		// For qualifiers evpW0( & 0x7FFF ) is the offset in the qualToOi array
		// And evpW1( & 0x7FFF ) is the qualifier number.
		LPQOI CurrentQualToOiStart = PtrAddBytes(QualToOiList, p1 & 0x7FFF);
		LPQOI CurrentQualToOi = CurrentQualToOiStart;

		int numSelected = 0;

		// Loop through all objects associated with this qualifier
		for (CurrentQualToOi;
			CurrentQualToOi->qoiOiList >= 0;
			CurrentQualToOi = PtrAddBytes(CurrentQualToOi, 4) )
		{
			LPOIL CurrentOi = GetOILPtr(OiList, CurrentQualToOi->qoiOiList); //get a pointer to the objectInfo
			if(CurrentOi->oilNObjects <= 0) //skip if there are none of the object
				continue;

			bool prevSelected = (CurrentOi->oilEventCount == rhPtr->rh2.rh2EventCount); //find out if conditions have selected any param1's yet

			numSelected += CurrentOi->oilNObjects;

			if(!prevSelected) //if there is no selection then we don't need to do anything
			{
				continue;
			}

			//tell mmf that the current selection applies to the last event, so it re-creates the selection
			CurrentOi->oilEventCount = rhPtr->rh2.rh2EventCount - 1;
		}

		return (numSelected > 0);
	}
	else
	{
		LPOIL CurrentOi = GetOILPtr(OiList, p1); //get a pointer to the objectInfo for param1
		if(CurrentOi->oilNObjects <= 0) //return if there are none of the object
			return false;

		bool prevSelected = (CurrentOi->oilEventCount == rhPtr->rh2.rh2EventCount); //find out if conditions have selected any param1's yet
		if(!prevSelected) //if there's no current selection then we don't have to do anything, mmf already assumes we mean all objects
			return true;

		//tell mmf that the current selection applies to the last event, so it re-creates the selection
		CurrentOi->oilEventCount = rhPtr->rh2.rh2EventCount - 1;
		return true;
	}
}

// -----------------
// Select Highest/Lowest Alt V( )
// -----------------
// Selects the single object of type p1 with the highest/lowest Alt. Value(p2)
// In the case of a tie picks the first one
// 

long WINAPI DLLExport CND_SelectHighestAltV(LPRDATA rdPtr, long param1, long param2)
{
	// For objects evpW0 is the index in the OiList
	// And evpW1 is the Oi number.
	short p1 = ((eventParam*)param1)->evp.evpW.evpW0;
	short p2 = (short)param2;

	if(p2<0 || p2>26) // invalid Alt. Value
		return false;

	const LPRH rhPtr = rdPtr->rHo.hoAdRunHeader; //get a pointer to the mmf runtime header
	const LPOBL ObjectList = rhPtr->rhObjectList; //get a pointer to the mmf object list
	const LPOIL OiList = rhPtr->rhOiList; //get a pointer to the mmf object info list
	const LPQOI QualToOiList = rhPtr->rhQualToOiList; //get a pointer to the mmf qualifier to Oi list

	if(p1 & 0x8000) // dealing with a qualifier...
	{
		// For qualifiers evpW0( & 0x7FFF ) is the offset in the qualToOi array
		// And evpW1( & 0x7FFF ) is the qualifier number.
		LPQOI CurrentQualToOiStart = PtrAddBytes(QualToOiList, p1 & 0x7FFF);
		LPQOI CurrentQualToOi = CurrentQualToOiStart;

		headerObject* HighestObject = NULL;

		// Loop through all objects associated with this qualifier
		for (CurrentQualToOi; CurrentQualToOi->qoiOiList >= 0;
			CurrentQualToOi = PtrAddBytes(CurrentQualToOi, 4) )
		{
			LPOIL CurrentOi = GetOILPtr(OiList, CurrentQualToOi->qoiOiList); //get a pointer to the objectInfo
			if(CurrentOi->oilNObjects <= 0) //skip if there are none of the object
				continue;

			bool prevSelected = (CurrentOi->oilEventCount == rhPtr->rh2.rh2EventCount); //find out if conditions have selected any of this object yet
			if(prevSelected && CurrentOi->oilNumOfSelected <= 0) //if it thinks there are but there's 0 (??) then skip
				continue;

			if(!IsSet(CurrentOi->oilOEFlags, OEFLAG_VALUES)) //skip if the object has no Alt. Values
			{
				CurrentOi->oilEventCount = rhPtr->rh2.rh2EventCount; //tell mmf that our condition selects objects for this event
				CurrentOi->oilListSelected = -1; //set the first selected object to invalid_object
				CurrentOi->oilNumOfSelected = 0; // set the number of selected to 0
				continue;
			}

			headerObject* CurrentObject;
			if(!prevSelected) //if none have been selected then loop through all objects
				CurrentObject = ObjectList[CurrentOi->oilObject].oblOffset;
			else //otherwise loop through the current selection
				CurrentObject = ObjectList[CurrentOi->oilListSelected].oblOffset;

			CurrentOi->oilEventCount = rhPtr->rh2.rh2EventCount; //tell mmf that our condition selects objects for this event
			CurrentOi->oilListSelected = -1; //set the first selected object to invalid_object
			CurrentOi->oilNumOfSelected = 0; // set the number of selected to 0

			// the first valid object found is automatically the "highest"
			if (!HighestObject)
			{
				HighestObject = CurrentObject;

				// advance CurrentObject to point to the next selected one.
				if (!prevSelected) {
					if(CurrentObject->hoOiNext < 0)
						CurrentObject = NULL;
					else
						CurrentObject = ObjectList[CurrentObject->hoOiNext].oblOffset;
				} else {
					if(CurrentObject->hoNextSelected < 0)
						CurrentObject = NULL;
					else
						CurrentObject = ObjectList[CurrentObject->hoNextSelected].oblOffset;
				}
			}

			while(CurrentObject)
			{
				if (getAlterableValue(CurrentObject, p2) > getAlterableValue(HighestObject, p2))
				{
					HighestObject = CurrentObject;
				}

				if(!prevSelected) {
					if(CurrentObject->hoOiNext < 0)
						CurrentObject = NULL;
					else
						CurrentObject = ObjectList[CurrentObject->hoOiNext].oblOffset;
				} else {
					if(CurrentObject->hoNextSelected < 0)
						CurrentObject = NULL;
					else
						CurrentObject = ObjectList[CurrentObject->hoNextSelected].oblOffset;
				}
			}
		}

		if (HighestObject)
		{
			HighestObject->hoOiList->oilNumOfSelected = 1; // selected 1 object
			HighestObject->hoOiList->oilListSelected = HighestObject->hoNumber; // set the selected object
			HighestObject->hoNextSelected = -1; // set the next selected to invalid_object

			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		LPOIL CurrentOi = GetOILPtr(OiList, p1); //get a pointer to the objectInfo for param1
		if(CurrentOi->oilNObjects <= 0) //return if there are none of the object
			return false;
		if(!IsSet(CurrentOi->oilOEFlags, OEFLAG_VALUES)) //return if the object has no Alt. Values
			return false;

		bool prevSelected = (CurrentOi->oilEventCount == rhPtr->rh2.rh2EventCount); //find out if conditions have selected any param1's yet
		if(prevSelected && CurrentOi->oilNumOfSelected <= 0) //if it thinks there are but there's 0 (??) then return
			return false;

		CurrentOi->oilEventCount = rhPtr->rh2.rh2EventCount; //tell mmf that our condition selects objects for this event

		headerObject* HighestObject;
		{
			headerObject* CurrentObject;
			if(!prevSelected) //if none have been selected then loop through all objects
				CurrentObject = ObjectList[CurrentOi->oilObject].oblOffset;
			else //otherwise loop through the current selection
				CurrentObject = ObjectList[CurrentOi->oilListSelected].oblOffset;

			HighestObject = CurrentObject;
			while(1)
			{
				if(!prevSelected) {
					if(CurrentObject->hoOiNext < 0)
						break;
					else
						CurrentObject = ObjectList[CurrentObject->hoOiNext].oblOffset;
				} else {
					if(CurrentObject->hoNextSelected < 0)
						break;
					else
						CurrentObject = ObjectList[CurrentObject->hoNextSelected].oblOffset;
				}

				if (getAlterableValue(CurrentObject, p2) > getAlterableValue(HighestObject, p2))
				{
					HighestObject = CurrentObject;
				}
			}
		}

		CurrentOi->oilNumOfSelected = 1; // selected 1 object
		CurrentOi->oilListSelected = HighestObject->hoNumber; // set the selected object
		HighestObject->hoNextSelected = -1;

		return true;
	}
}

long WINAPI DLLExport CND_SelectLowestAltV(LPRDATA rdPtr, long param1, long param2)
{
	// For objects evpW0 is the index in the OiList
	// And evpW1 is the Oi number.
	short p1 = ((eventParam*)param1)->evp.evpW.evpW0;
	short p2 = (short)param2;

	if(p2<0 || p2>26) // invalid Alt. Value
		return false;

	const LPRH rhPtr = rdPtr->rHo.hoAdRunHeader; //get a pointer to the mmf runtime header
	const LPOBL ObjectList = rhPtr->rhObjectList; //get a pointer to the mmf object list
	const LPOIL OiList = rhPtr->rhOiList; //get a pointer to the mmf object info list
	const LPQOI QualToOiList = rhPtr->rhQualToOiList; //get a pointer to the mmf qualifier to Oi list

	if(p1 & 0x8000) // dealing with a qualifier...
	{
		// For qualifiers evpW0( & 0x7FFF ) is the offset in the qualToOi array
		// And evpW1( & 0x7FFF ) is the qualifier number.
		LPQOI CurrentQualToOiStart = PtrAddBytes(QualToOiList, p1 & 0x7FFF);
		LPQOI CurrentQualToOi = CurrentQualToOiStart;

		headerObject* LowestObject = NULL;

		// Loop through all objects associated with this qualifier
		for (CurrentQualToOi; CurrentQualToOi->qoiOiList >= 0;
			CurrentQualToOi = PtrAddBytes(CurrentQualToOi, 4) )
		{
			LPOIL CurrentOi = GetOILPtr(OiList, CurrentQualToOi->qoiOiList); //get a pointer to the objectInfo
			if(CurrentOi->oilNObjects <= 0) //skip if there are none of the object
				continue;

			bool prevSelected = (CurrentOi->oilEventCount == rhPtr->rh2.rh2EventCount); //find out if conditions have selected any of this object yet
			if(prevSelected && CurrentOi->oilNumOfSelected <= 0) //if it thinks there are but there's 0 (??) then skip
				continue;

			if(!IsSet(CurrentOi->oilOEFlags, OEFLAG_VALUES)) //skip if the object has no Alt. Values
			{
				CurrentOi->oilEventCount = rhPtr->rh2.rh2EventCount; //tell mmf that our condition selects objects for this event
				CurrentOi->oilListSelected = -1; //set the first selected object to invalid_object
				CurrentOi->oilNumOfSelected = 0; // set the number of selected to 0
				continue;
			}

			headerObject* CurrentObject;
			if(!prevSelected) //if none have been selected then loop through all objects
				CurrentObject = ObjectList[CurrentOi->oilObject].oblOffset;
			else //otherwise loop through the current selection
				CurrentObject = ObjectList[CurrentOi->oilListSelected].oblOffset;

			CurrentOi->oilEventCount = rhPtr->rh2.rh2EventCount; //tell mmf that our condition selects objects for this event
			CurrentOi->oilListSelected = -1; //set the first selected object to invalid_object
			CurrentOi->oilNumOfSelected = 0; // set the number of selected to 0

			// the first valid object found is automatically the "highest"
			if (!LowestObject)
			{
				LowestObject = CurrentObject;

				// advance CurrentObject to point to the next selected one.
				if (!prevSelected) {
					if(CurrentObject->hoOiNext < 0)
						CurrentObject = NULL;
					else
						CurrentObject = ObjectList[CurrentObject->hoOiNext].oblOffset;
				} else {
					if(CurrentObject->hoNextSelected < 0)
						CurrentObject = NULL;
					else
						CurrentObject = ObjectList[CurrentObject->hoNextSelected].oblOffset;
				}
			}

			while(CurrentObject)
			{
				if (getAlterableValue(CurrentObject, p2) < getAlterableValue(LowestObject, p2))
				{
					LowestObject = CurrentObject;
				}

				if(!prevSelected) {
					if(CurrentObject->hoOiNext < 0)
						CurrentObject = NULL;
					else
						CurrentObject = ObjectList[CurrentObject->hoOiNext].oblOffset;
				} else {
					if(CurrentObject->hoNextSelected < 0)
						CurrentObject = NULL;
					else
						CurrentObject = ObjectList[CurrentObject->hoNextSelected].oblOffset;
				}
			}
		}

		if (LowestObject)
		{
			LowestObject->hoOiList->oilNumOfSelected = 1; // selected 1 object
			LowestObject->hoOiList->oilListSelected = LowestObject->hoNumber; // set the selected object
			LowestObject->hoNextSelected = -1; // set the next selected to invalid_object

			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		LPOIL CurrentOi = GetOILPtr(OiList, p1); //get a pointer to the objectInfo for param1
		if(CurrentOi->oilNObjects <= 0) //return if there are none of the object
			return false;
		if(!IsSet(CurrentOi->oilOEFlags, OEFLAG_VALUES)) //return if the object has no Alt. Values
			return false;

		bool prevSelected = (CurrentOi->oilEventCount == rhPtr->rh2.rh2EventCount); //find out if conditions have selected any param1's yet
		if(prevSelected && CurrentOi->oilNumOfSelected <= 0) //if it thinks there are but there's 0 (??) then return
			return false;

		CurrentOi->oilEventCount = rhPtr->rh2.rh2EventCount; //tell mmf that our condition selects objects for this event

		headerObject* LowestObject;
		{
			headerObject* CurrentObject;
			if(!prevSelected) //if none have been selected then loop through all objects
				CurrentObject = ObjectList[CurrentOi->oilObject].oblOffset;
			else //otherwise loop through the current selection
				CurrentObject = ObjectList[CurrentOi->oilListSelected].oblOffset;

			LowestObject = CurrentObject;
			while(1)
			{
				if(!prevSelected) {
					if(CurrentObject->hoOiNext < 0)
						break;
					else
						CurrentObject = ObjectList[CurrentObject->hoOiNext].oblOffset;
				} else {
					if(CurrentObject->hoNextSelected < 0)
						break;
					else
						CurrentObject = ObjectList[CurrentObject->hoNextSelected].oblOffset;
				}

				if (getAlterableValue(CurrentObject, p2) < getAlterableValue(LowestObject, p2))
				{
					LowestObject = CurrentObject;
				}
			}
		}

		CurrentOi->oilNumOfSelected = 1; // selected 1 object
		CurrentOi->oilListSelected = LowestObject->hoNumber; // set the selected object
		LowestObject->hoNextSelected = -1;

		return true;
	}
}

// -----------------
// Select Tied Highest/Lowest Alt V( )
// -----------------
// Selects all the objects of type p1 with the tied highest/lowest Alt. Value(p2)
// 

//long WINAPI DLLExport CND_SelectTiedHighestAltV(LPRDATA rdPtr, long param1, long param2)
//{
//	short p1 = ((eventParam*)param1)->evp.evpW.evpW0;
//	short p2 = (short)param2;
//
//	if(p1<0) // dealing with a qualifier...
//		return false;
//
//	return false;
//}
//
//long WINAPI DLLExport CND_SelectTiedLowestAltV(LPRDATA rdPtr, long param1, long param2)
//{
//	short p1 = ((eventParam*)param1)->evp.evpW.evpW0;
//	short p2 = (short)param2;
//
//	if(p1<0) // dealing with a qualifier...
//		return false;
//
//	return false;
//}

// -----------------
// Select Frontmost/Rearmost( )
// -----------------
// Selects the single frontmost/rearmost object of type p1
// In the case of a tie picks the first one
// 

// The GetTopMost function given to me by Yves
/*
headerObject* GetTopMost(npWin idWin, int nLayer) 
{ 
npSpr pSpr; 
headerObject* pRo = NULL; 
DWORD dwPrevFlags = 0; 

if ( nLayer != -1 ) 
dwPrevFlags = GS_SAMELAYER; 

for (pSpr = GetLastSprite(idWin, nLayer, 0); pSpr != NULL; pSpr = GetPrevSprite(idWin, pSpr, dwPrevFlags)) 
{ 
if ( (GetSpriteFlags(idWin, pSpr) & SF_TOKILL) == 0 ) 
{ 
pRo = (headerObject*)GetSpriteExtra(idWin, pSpr); 
break; 
} 
} 
return pRo; 
}*/

long WINAPI DLLExport CND_SelectFrontmost(LPRDATA rdPtr, long param1, long param2)
{
	short p1 = ((eventParam*)param1)->evp.evpW.evpW0;

	const LPRH rhPtr = rdPtr->rHo.hoAdRunHeader; //get a pointer to the mmf runtime header
	const LPOBL ObjectList = rhPtr->rhObjectList; //get a pointer to the mmf object list
	const LPOIL OiList = rhPtr->rhOiList; //get a pointer to the mmf object info list
	const LPQOI QualToOiList = rhPtr->rhQualToOiList; //get a pointer to the mmf qualifier to Oi list

	if(p1 & 0x8000) // dealing with a qualifier...
	{
		// For qualifiers evpW0( & 0x7FFF ) is the offset in the qualToOi array
		// And evpW1( & 0x7FFF ) is the qualifier number.
		LPQOI CurrentQualToOiStart = PtrAddBytes(QualToOiList, p1 & 0x7FFF);
		LPQOI CurrentQualToOi = CurrentQualToOiStart;

		headerObject* FrontmostObject = NULL;

		// Loop through all objects associated with this qualifier
		for (CurrentQualToOi; CurrentQualToOi->qoiOiList >= 0;
			CurrentQualToOi = PtrAddBytes(CurrentQualToOi, 4) )
		{
			LPOIL CurrentOi = GetOILPtr(OiList, CurrentQualToOi->qoiOiList); //get a pointer to the objectInfo
			if(CurrentOi->oilNObjects <= 0) //skip if there are none of the object
				continue;

			bool prevSelected = (CurrentOi->oilEventCount == rhPtr->rh2.rh2EventCount); //find out if conditions have selected any of this object yet
			if(prevSelected && CurrentOi->oilNumOfSelected <= 0) //if it thinks there are but there's 0 (??) then skip
				continue;

			if(!IsSet(CurrentOi->oilOEFlags, OEFLAG_SPRITES)) //skip if the object is not a sprite (and is therefore not in the mmf display list)
			{
				CurrentOi->oilEventCount = rhPtr->rh2.rh2EventCount; //tell mmf that our condition selects objects for this event
				CurrentOi->oilListSelected = -1; //set the first selected object to invalid_object
				CurrentOi->oilNumOfSelected = 0; // set the number of selected to 0
				continue;
			}

			headerObject* CurrentObject;
			if(!prevSelected) //if none have been selected then loop through all objects
				CurrentObject = ObjectList[CurrentOi->oilObject].oblOffset;
			else //otherwise loop through the current selection
				CurrentObject = ObjectList[CurrentOi->oilListSelected].oblOffset;

			CurrentOi->oilEventCount = rhPtr->rh2.rh2EventCount; //tell mmf that our condition selects objects for this event
			CurrentOi->oilListSelected = -1; //set the first selected object to invalid_object
			CurrentOi->oilNumOfSelected = 0; // set the number of selected to 0

			// the first valid object found is automatically the "frontmost"
			if (!FrontmostObject)
			{
				// Find an object with a sprite to start with
				while(CurrentObject && !getrCom(CurrentObject)->rcSprite)
				{
					if(!prevSelected) {
						if(CurrentObject->hoOiNext < 0)
							CurrentObject = NULL;
						else
							CurrentObject = ObjectList[CurrentObject->hoOiNext].oblOffset;
					} else {
						if(CurrentObject->hoNextSelected < 0)
							CurrentObject = NULL;
						else
							CurrentObject = ObjectList[CurrentObject->hoNextSelected].oblOffset;
					}
				}

				if (!CurrentObject)
				{
					continue;
				}

				FrontmostObject = CurrentObject;

				// advance CurrentObject to point to the next one.
				if (!prevSelected) {
					if(CurrentObject->hoOiNext < 0)
						CurrentObject = NULL;
					else
						CurrentObject = ObjectList[CurrentObject->hoOiNext].oblOffset;
				} else {
					if(CurrentObject->hoNextSelected < 0)
						CurrentObject = NULL;
					else
						CurrentObject = ObjectList[CurrentObject->hoNextSelected].oblOffset;
				}
			}

			while(CurrentObject)
			{
				if(getrCom(CurrentObject)->rcSprite &&
					getrCom(CurrentObject)->rcSprite->sprZOrder > getrCom(FrontmostObject)->rcSprite->sprZOrder)
				{
					FrontmostObject = CurrentObject;
				}

				if(!prevSelected) {
					if(CurrentObject->hoOiNext < 0)
						CurrentObject = NULL;
					else
						CurrentObject = ObjectList[CurrentObject->hoOiNext].oblOffset;
				} else {
					if(CurrentObject->hoNextSelected < 0)
						CurrentObject = NULL;
					else
						CurrentObject = ObjectList[CurrentObject->hoNextSelected].oblOffset;
				}
			}
		}

		if (FrontmostObject)
		{
			FrontmostObject->hoOiList->oilNumOfSelected = 1; // selected 1 object
			FrontmostObject->hoOiList->oilListSelected = FrontmostObject->hoNumber; // set the selected object
			FrontmostObject->hoNextSelected = -1; // set the next selected to invalid_object

			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		LPOIL CurrentOi = GetOILPtr(OiList, p1); //get a pointer to the objectInfo for param1
		if(CurrentOi->oilNObjects <= 0) //return if there are none of the object
			return false;
		if(!IsSet(CurrentOi->oilOEFlags, OEFLAG_SPRITES)) //return if the object is not a sprite (and is therefore not in the mmf display list)
			return false;

		bool prevSelected = (CurrentOi->oilEventCount == rhPtr->rh2.rh2EventCount); //find out if conditions have selected any param1's yet
		if(prevSelected && CurrentOi->oilNumOfSelected <= 0) //if it thinks there are but there's 0 (??) then return
			return false;

		CurrentOi->oilEventCount = rhPtr->rh2.rh2EventCount; //tell mmf that our condition selects objects for this event

		headerObject* FrontmostObject = NULL;
		{
			headerObject* CurrentObject;
			if(!prevSelected) //if none have been selected then loop through all objects of this type
				CurrentObject = ObjectList[CurrentOi->oilObject].oblOffset;
			else //otherwise loop through the current selection
				CurrentObject = ObjectList[CurrentOi->oilListSelected].oblOffset;

			// Find an object with a sprite to start with
			while(CurrentObject && !getrCom(CurrentObject)->rcSprite)
			{
				if(!prevSelected) {
					if(CurrentObject->hoOiNext < 0)
						CurrentObject = NULL;
					else
						CurrentObject = ObjectList[CurrentObject->hoOiNext].oblOffset;
				} else {
					if(CurrentObject->hoNextSelected < 0)
						CurrentObject = NULL;
					else
						CurrentObject = ObjectList[CurrentObject->hoNextSelected].oblOffset;
				}
			}

			FrontmostObject = CurrentObject;

			while(CurrentObject)
			{
				if(!prevSelected) {
					if(CurrentObject->hoOiNext < 0)
						break;
					else
						CurrentObject = ObjectList[CurrentObject->hoOiNext].oblOffset;
				} else {
					if(CurrentObject->hoNextSelected < 0)
						break;
					else
						CurrentObject = ObjectList[CurrentObject->hoNextSelected].oblOffset;
				}

				//if(getrSpr(CurrentObject)->rsZOrder > getrSpr(FrontmostObject)->rsZOrder)
				if(getrCom(CurrentObject)->rcSprite &&
					getrCom(CurrentObject)->rcSprite->sprZOrder > getrCom(FrontmostObject)->rcSprite->sprZOrder)
				{
					FrontmostObject = CurrentObject;
				}
			}
		}

		if(FrontmostObject)
		{
			CurrentOi->oilNumOfSelected = 1; // selected 1 object
			CurrentOi->oilListSelected = FrontmostObject->hoNumber; // set the selected object
			FrontmostObject->hoNextSelected = -1;

			return true;
		}
		else
		{
			return false;
		}
	}
}

long WINAPI DLLExport CND_SelectRearmost(LPRDATA rdPtr, long param1, long param2)
{
	short p1 = ((eventParam*)param1)->evp.evpW.evpW0;

	const LPRH rhPtr = rdPtr->rHo.hoAdRunHeader; //get a pointer to the mmf runtime header
	const LPOBL ObjectList = rhPtr->rhObjectList; //get a pointer to the mmf object list
	const LPOIL OiList = rhPtr->rhOiList; //get a pointer to the mmf object info list
	const LPQOI QualToOiList = rhPtr->rhQualToOiList; //get a pointer to the mmf qualifier to Oi list

	if(p1 & 0x8000) // dealing with a qualifier...
	{
		// For qualifiers evpW0( & 0x7FFF ) is the offset in the qualToOi array
		// And evpW1( & 0x7FFF ) is the qualifier number.
		LPQOI CurrentQualToOiStart = PtrAddBytes(QualToOiList, p1 & 0x7FFF);
		LPQOI CurrentQualToOi = CurrentQualToOiStart;

		headerObject* RearmostObject = NULL;

		// Loop through all objects associated with this qualifier
		for (CurrentQualToOi; CurrentQualToOi->qoiOiList >= 0;
			CurrentQualToOi = PtrAddBytes(CurrentQualToOi, 4) )
		{
			LPOIL CurrentOi = GetOILPtr(OiList, CurrentQualToOi->qoiOiList); //get a pointer to the objectInfo
			if(CurrentOi->oilNObjects <= 0) //skip if there are none of the object
				continue;

			bool prevSelected = (CurrentOi->oilEventCount == rhPtr->rh2.rh2EventCount); //find out if conditions have selected any of this object yet
			if(prevSelected && CurrentOi->oilNumOfSelected <= 0) //if it thinks there are but there's 0 (??) then skip
				continue;

			if(!IsSet(CurrentOi->oilOEFlags, OEFLAG_SPRITES)) //skip if the object is not a sprite (and is therefore not in the mmf display list)
			{
				CurrentOi->oilEventCount = rhPtr->rh2.rh2EventCount; //tell mmf that our condition selects objects for this event
				CurrentOi->oilListSelected = -1; //set the first selected object to invalid_object
				CurrentOi->oilNumOfSelected = 0; // set the number of selected to 0
				continue;
			}

			headerObject* CurrentObject;
			if(!prevSelected) //if none have been selected then loop through all objects
				CurrentObject = ObjectList[CurrentOi->oilObject].oblOffset;
			else //otherwise loop through the current selection
				CurrentObject = ObjectList[CurrentOi->oilListSelected].oblOffset;

			CurrentOi->oilEventCount = rhPtr->rh2.rh2EventCount; //tell mmf that our condition selects objects for this event
			CurrentOi->oilListSelected = -1; //set the first selected object to invalid_object
			CurrentOi->oilNumOfSelected = 0; // set the number of selected to 0

			// the first valid object found is automatically the "frontmost"
			if (!RearmostObject)
			{
				// Find an object with a sprite to start with
				while(CurrentObject && !getrCom(CurrentObject)->rcSprite)
				{
					if(!prevSelected) {
						if(CurrentObject->hoOiNext < 0)
							CurrentObject = NULL;
						else
							CurrentObject = ObjectList[CurrentObject->hoOiNext].oblOffset;
					} else {
						if(CurrentObject->hoNextSelected < 0)
							CurrentObject = NULL;
						else
							CurrentObject = ObjectList[CurrentObject->hoNextSelected].oblOffset;
					}
				}

				if (!CurrentObject)
				{
					continue;
				}

				RearmostObject = CurrentObject;

				// advance CurrentObject to point to the next one.
				if (!prevSelected) {
					if(CurrentObject->hoOiNext < 0)
						CurrentObject = NULL;
					else
						CurrentObject = ObjectList[CurrentObject->hoOiNext].oblOffset;
				} else {
					if(CurrentObject->hoNextSelected < 0)
						CurrentObject = NULL;
					else
						CurrentObject = ObjectList[CurrentObject->hoNextSelected].oblOffset;
				}
			}

			while(CurrentObject)
			{
				if(getrCom(CurrentObject)->rcSprite &&
					getrCom(CurrentObject)->rcSprite->sprZOrder < getrCom(RearmostObject)->rcSprite->sprZOrder)
				{
					RearmostObject = CurrentObject;
				}

				if(!prevSelected) {
					if(CurrentObject->hoOiNext < 0)
						CurrentObject = NULL;
					else
						CurrentObject = ObjectList[CurrentObject->hoOiNext].oblOffset;
				} else {
					if(CurrentObject->hoNextSelected < 0)
						CurrentObject = NULL;
					else
						CurrentObject = ObjectList[CurrentObject->hoNextSelected].oblOffset;
				}
			}
		}

		if (RearmostObject)
		{
			RearmostObject->hoOiList->oilNumOfSelected = 1; // selected 1 object
			RearmostObject->hoOiList->oilListSelected = RearmostObject->hoNumber; // set the selected object
			RearmostObject->hoNextSelected = -1; // set the next selected to invalid_object

			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		LPOIL CurrentOi = GetOILPtr(OiList, p1); //get a pointer to the objectInfo for param1
		if(CurrentOi->oilNObjects <= 0) //return if there are none of the object
			return false;
		if(!IsSet(CurrentOi->oilOEFlags, OEFLAG_SPRITES)) //return if the object is not a sprite (and is therefore not in the mmf display list)
			return false;

		bool prevSelected = (CurrentOi->oilEventCount == rhPtr->rh2.rh2EventCount); //find out if conditions have selected any param1's yet
		if(prevSelected && CurrentOi->oilNumOfSelected <= 0) //if it thinks there are but there's 0 (??) then return
			return false;

		CurrentOi->oilEventCount = rhPtr->rh2.rh2EventCount; //tell mmf that our condition selects objects for this event

		headerObject* RearmostObject = NULL;
		{
			headerObject* CurrentObject;
			if(!prevSelected) //if none have been selected then loop through all objects of this type
				CurrentObject = ObjectList[CurrentOi->oilObject].oblOffset;
			else //otherwise loop through the current selection
				CurrentObject = ObjectList[CurrentOi->oilListSelected].oblOffset;

			// Find an object with a sprite to start with
			while(CurrentObject && !getrCom(CurrentObject)->rcSprite)
			{
				if(!prevSelected) {
					if(CurrentObject->hoOiNext < 0)
						CurrentObject = NULL;
					else
						CurrentObject = ObjectList[CurrentObject->hoOiNext].oblOffset;
				} else {
					if(CurrentObject->hoNextSelected < 0)
						CurrentObject = NULL;
					else
						CurrentObject = ObjectList[CurrentObject->hoNextSelected].oblOffset;
				}
			}

			RearmostObject = CurrentObject;

			while(CurrentObject)
			{
				if(!prevSelected) {
					if(CurrentObject->hoOiNext < 0)
						break;
					else
						CurrentObject = ObjectList[CurrentObject->hoOiNext].oblOffset;
				} else {
					if(CurrentObject->hoNextSelected < 0)
						break;
					else
						CurrentObject = ObjectList[CurrentObject->hoNextSelected].oblOffset;
				}

				//if(getrSpr(CurrentObject)->rsZOrder > getrSpr(RearmostObject)->rsZOrder)
				if(getrCom(CurrentObject)->rcSprite &&
					getrCom(CurrentObject)->rcSprite->sprZOrder < getrCom(RearmostObject)->rcSprite->sprZOrder)
				{
					RearmostObject = CurrentObject;
				}
			}
		}

		if(RearmostObject)
		{
			CurrentOi->oilNumOfSelected = 1; // selected 1 object
			CurrentOi->oilListSelected = RearmostObject->hoNumber; // set the selected object
			RearmostObject->hoNextSelected = -1;

			return true;
		}
		else
		{
			return false;
		}
	}
}

// -----------------
// Compare to Number of Selected( )
// -----------------
// Returns the number of selected objects of type p1 for mmf to compare against
// 

long WINAPI DLLExport CND_CompareSelected(LPRDATA rdPtr, long param1, long param2)
{
	short p1 = ((eventParam*)param1)->evp.evpW.evpW0;      // p1 = object type
	Comparison p2 = (Comparison)((short*)param1)[8]; // p2 = comparison type
	long p3 = param2;                    // p3 = comparison value

	const LPRH rhPtr = rdPtr->rHo.hoAdRunHeader; //get a pointer to the mmf runtime header
	const LPOIL OiList = rhPtr->rhOiList; //get a pointer to the mmf object info list
	const LPQOI QualToOiList = rhPtr->rhQualToOiList; //get a pointer to the mmf qualifier to Oi list

	if(p1 & 0x8000) // dealing with a qualifier...
	{
		// For qualifiers evpW0( & 0x7FFF ) is the offset in the qualToOi array
		// And evpW1( & 0x7FFF ) is the qualifier number.
		LPQOI CurrentQualToOiStart = PtrAddBytes(QualToOiList, p1 & 0x7FFF);
		LPQOI CurrentQualToOi = CurrentQualToOiStart;

		int numSelected = 0;

		// Loop through all objects associated with this qualifier
		for (CurrentQualToOi;
			CurrentQualToOi->qoiOiList >= 0;
			CurrentQualToOi = PtrAddBytes(CurrentQualToOi, 4) )
		{
			LPOIL CurrentOi = GetOILPtr(OiList, CurrentQualToOi->qoiOiList); //get a pointer to the objectInfo
			if(CurrentOi->oilNObjects <= 0) //skip if there are none of the object
				continue;

			bool prevSelected = (CurrentOi->oilEventCount == rhPtr->rh2.rh2EventCount); //find out if conditions have selected any param1's yet
			if(prevSelected && CurrentOi->oilNumOfSelected <= 0) //if it thinks there are but there's 0 (??) then skip
				continue;

			if(prevSelected)
				numSelected += CurrentOi->oilNumOfSelected;
			else
				numSelected += CurrentOi->oilNObjects;
		}

		return numSelected;
	}
	else
	{
		LPOIL CurrentOi = GetOILPtr(OiList, p1); //get a pointer to the objectInfo for param1
		if(CurrentOi->oilNObjects <= 0) //return 0 if there are none of the object
			return 0;

		bool prevSelected = (CurrentOi->oilEventCount == rhPtr->rh2.rh2EventCount); //find out if conditions have selected any param1's yet
		if(prevSelected && CurrentOi->oilNumOfSelected <= 0) //if it thinks there are but there's 0 (??) then return 0
			return 0;

		if(prevSelected)
			return CurrentOi->oilNumOfSelected;
		else
			return CurrentOi->oilNObjects;
	}
}

/*long WINAPI DLLExport CND_SelectByZ(LPRDATA rdPtr, long param1, long param2)
{
	short p1 = ((eventParam*)param1)->evp.evpW.evpW0;      // p1 = object type
	Comparison p2 = (Comparison)((short*)param1)[8]; // p2 = comparison type
	long p3 = param2;                    // p3 = comparison value

	if(p1<0) // dealing with a qualifier...
		return Param_Comparison_false(p2, p3);

	const LPRH rhPtr = rdPtr->rHo.hoAdRunHeader; //get a pointer to the mmf runtime header
	const LPOBL ObjectList = rhPtr->rhObjectList; //get a pointer to the mmf object list
	const LPOIL OiList = rhPtr->rhOiList; //get a pointer to the mmf object info list

	LPOIL CurrentOi = GetOILPtr(OiList, p1); //get a pointer to the objectInfo for param1
	if(CurrentOi->oilNObjects <= 0) //return if there are none of the object
		return Param_Comparison_false(p2, p3);
	if(!IsSet(CurrentOi->oilOEFlags, OEFLAG_SPRITES)) //return if the object is not a sprite (has no Z-order to test)
		return Param_Comparison_false(p2, p3);

	bool prevSelected = (CurrentOi->oilEventCount == rhPtr->rh2.rh2EventCount); //find out if conditions have selected any param1's yet
	if(prevSelected && CurrentOi->oilNumOfSelected <= 0) //if it thinks there are but there's 0 (??) then return
		return Param_Comparison_false(p2, p3);

	CurrentOi->oilEventCount = rhPtr->rh2.rh2EventCount; //tell mmf that our condition selects objects for this event

	headerObject* LastSelectedObject = 0;
	{
		headerObject* CurrentObject;
		if(!prevSelected) //if none have been selected then loop through all objects
			CurrentObject = ObjectList[CurrentOi->oilObject].oblOffset;
		else //otherwise loop through the current selection
			CurrentObject = ObjectList[CurrentOi->oilListSelected].oblOffset;

		CurrentOi->oilListSelected = -1; // Reset Selection
		CurrentOi->oilNumOfSelected = 0;

		while(1)
		{
			//if(getrSpr(CurrentObject)->rsZOrder < getrSpr(RearmostObject)->rsZOrder)
			if(Param_Comparison_Test(p2, getrCom(CurrentObject)->rcSprite->sprZOrder-2, p3))
			{
				if(CurrentOi->oilNumOfSelected > 0)
					LastSelectedObject->hoNextSelected = CurrentObject->hoNumber;
				else
					CurrentOi->oilListSelected = CurrentObject->hoNumber;
				LastSelectedObject = CurrentObject;
				CurrentOi->oilNumOfSelected++;
			}

			if(!prevSelected) {
				if(CurrentObject->hoOiNext < 0)
					break;
				else
					CurrentObject = ObjectList[CurrentObject->hoOiNext].oblOffset;
			} else {
				if(CurrentObject->hoNextSelected < 0)
					break;
				else
					CurrentObject = ObjectList[CurrentObject->hoNextSelected].oblOffset;
			}
		}
	}

	if(CurrentOi->oilNumOfSelected > 0)
	{
		LastSelectedObject->hoNextSelected = -1;
		return Param_Comparison_true(p2, p3);
	}
	else
		return Param_Comparison_false(p2, p3);
}*/


// ============================================================================
//
// ACTIONS ROUTINES
// 
// ============================================================================


// ============================================================================
//
// EXPRESSIONS ROUTINES
// 
// ============================================================================


long WINAPI DLLExport EXP_GetSelectedByName(LPRDATA rdPtr, long param1)
{
	char* p1 = (char*)CNC_GetFirstExpressionParameter(rdPtr, param1, TYPE_STRING);

	const LPRH rhPtr = rdPtr->rHo.hoAdRunHeader; //get a pointer to the mmf runtime header
	const LPOIL OiList = rhPtr->rhOiList; //get a pointer to the mmf object info list
	const LPMV pMv = rhPtr->rh4.rh4Mv;

	WCHAR strw[OINAME_SIZE];
	bool bUnicode = ( pMv->mvCallFunction(NULL, EF_ISUNICODE, 0, 0, 0) != 0 );
	if (bUnicode)
	{
		WORD wCodePage = (WORD)pMv->mvCallFunction(NULL, EF_GETAPPCODEPAGE, (LPARAM)rhPtr->rhApp, 0, 0);
		int Chars = MultiByteToWideChar(wCodePage, 0, p1, -1, strw, OINAME_SIZE);
		if (Chars == 0)
		{
			return 0;
		}
	}

	for (int i = 0; i < rhPtr->rhNumberOi; i++)
	{
		LPOIL CurrentOi = GetOILPtr(OiList, i); //get a pointer to the objectInfo
		int cmpres;
		if (bUnicode)
			cmpres = _wcsnicmp(strw, (LPCWSTR)CurrentOi->oilName, OINAME_SIZE);
		else
			cmpres = _strnicmp(p1, (LPCSTR)CurrentOi->oilName, OINAME_SIZE);
		if (cmpres == 0)
		{
			if(CurrentOi->oilEventCount == rhPtr->rh2.rh2EventCount) //find out if conditions have selected any p1's yet
				return CurrentOi->oilNumOfSelected;
			else
				return CurrentOi->oilNObjects;
		}
	}

	return 0;
}

long WINAPI DLLExport EXP_GetSelectedByFixed(LPRDATA rdPtr, long param1)
{
	long p1 = CNC_GetFirstExpressionParameter(rdPtr, param1, TYPE_INT);

	const LPRH rhPtr = rdPtr->rHo.hoAdRunHeader; //get a pointer to the mmf runtime header
	const LPOBL ObjectList = rhPtr->rhObjectList; //get a pointer to the mmf object list
	const LPOIL OiList = rhPtr->rhOiList; //get a pointer to the mmf object info list

	long CurrentId = 0x0000FFFF & p1;
	if(CurrentId < 0 || CurrentId > rhPtr->rhMaxObjects) // Object index is invalid
		return 0;

	headerObject* CurrentObject = ObjectList[CurrentId].oblOffset;
	if(CurrentObject == 0 || (CurrentObject->hoCreationId << 16) != (0xFFFF0000 & p1)) // Object doesn't exist at this index or the creation id is different
		return 0;

	if(CurrentObject->hoOiList->oilEventCount == rhPtr->rh2.rh2EventCount) //find out if conditions have selected any p1's yet
		return CurrentObject->hoOiList->oilNumOfSelected;
	else
		return CurrentObject->hoOiList->oilNObjects;

	return 0;
}

long WINAPI DLLExport EXP_GetNameByFixed(LPRDATA rdPtr, long param1)
{
	long p1 = CNC_GetFirstExpressionParameter(rdPtr, param1, TYPE_INT);

	const LPRH rhPtr = rdPtr->rHo.hoAdRunHeader; //get a pointer to the mmf runtime header
	const LPOBL ObjectList = rhPtr->rhObjectList; //get a pointer to the mmf object list
	const LPOIL OiList = rhPtr->rhOiList; //get a pointer to the mmf object info list
	const LPMV pMv = rhPtr->rh4.rh4Mv;

	long CurrentId = 0x0000FFFF & p1;
	if(CurrentId < 0 || CurrentId > rhPtr->rhMaxObjects) // Object index is invalid
		return PackString("");

	headerObject* CurrentObject = ObjectList[CurrentId].oblOffset;
	if(CurrentObject == 0 || (CurrentObject->hoCreationId << 16) != (0xFFFF0000 & p1)) // Object doesn't exist at this index or the creation id is different
		return PackString("");

	const LPOIL CurrentOi = CurrentObject->hoOiList; //get a pointer to the objectInfo

	const char* Name = (char*)CurrentOi->oilName;
	bool bUnicode = ( pMv->mvCallFunction(NULL, EF_ISUNICODE, 0, 0, 0) != 0 );
	if (bUnicode)
	{
		Name = (char *)callRunTimeFunction(rdPtr, RFUNCTION_GETSTRINGSPACE_EX, 0, OINAME_SIZE);
		WORD wCodePage = (WORD)pMv->mvCallFunction(NULL, EF_GETAPPCODEPAGE, (LPARAM)rhPtr->rhApp, 0, 0);
		int Chars = WideCharToMultiByte(wCodePage, 0, (LPCWSTR)CurrentOi->oilName, -1, (LPSTR)Name, OINAME_SIZE, NULL, NULL);
		if (Chars == 0)
		{
			return PackString("");
		}
	}

	return PackString(Name);
}

/*long WINAPI DLLExport EXP_GetZOrderByName(LPRDATA rdPtr, long param1)
{
	char* p1 = (char*)CNC_GetFirstExpressionParameter(rdPtr, param1, TYPE_STRING);

	const LPRH rhPtr = rdPtr->rHo.hoAdRunHeader; //get a pointer to the mmf runtime header
	const LPOBL ObjectList = rhPtr->rhObjectList; //get a pointer to the mmf object list
	const LPOIL OiList = rhPtr->rhOiList; //get a pointer to the mmf object info list

	for(int i=0; i<rhPtr->rhNumberOi; i++)
	{
		LPOIL CurrentOi = GetOILPtr(OiList, i); //get a pointer to the objectInfo
		if(_strnicmp(p1, (char*)CurrentOi->oilName, 24) == 0)
		{
			if(CurrentOi->oilEventCount == rhPtr->rh2.rh2EventCount) // if conditions selected any p1's then we can use mmf's oilCurrentOi marker
			{
				headerObject* CurrentObject = ObjectList[CurrentOi->oilCurrentOi].oblOffset;
				if(getrCom(CurrentObject)->rcSprite)
					return getrCom(CurrentObject)->rcSprite->sprZOrder-2;
				else
					return getrSpr(CurrentObject)->rsZOrder-2;
			}
			else
			{

			}
			//else
			//	return CurrentOi->oilNObjects;
		}
	}

	return 0;
}

long WINAPI DLLExport EXP_GetZOrderByFixed(LPRDATA rdPtr, long param1)
{
	long p1 = CNC_GetFirstExpressionParameter(rdPtr, param1, TYPE_INT);

	const LPRH rhPtr = rdPtr->rHo.hoAdRunHeader; //get a pointer to the mmf runtime header
	const LPOBL ObjectList = rhPtr->rhObjectList; //get a pointer to the mmf object list
	const LPOIL OiList = rhPtr->rhOiList; //get a pointer to the mmf object info list

	long CurrentId = 0x0000FFFF & p1;
	if(CurrentId < 0 || CurrentId > rhPtr->rhMaxObjects) // Object index is invalid
		return -1;

	headerObject* CurrentObject = ObjectList[CurrentId].oblOffset;
	if(CurrentObject == 0 || (CurrentObject->hoCreationId << 16) != (0xFFFF0000 & p1)) // Object doesn't exist at this index or the creation id is different
		return -1;

	if(!IsSet(CurrentObject->hoOEFlags, OEFLAG_SPRITES)) //return if the object is not a sprite (has no Z-order to test)
		return -1;

	if(getrCom(CurrentObject)->rcSprite)
        return getrCom(CurrentObject)->rcSprite->sprZOrder-2;
	else
		return getrSpr(CurrentObject)->rsZOrder-2;
}*/


// ----------------------------------------------------------
// Condition / Action / Expression jump table
// ----------------------------------------------------------
// Contains the address inside the extension of the different
// routines that handle the action, conditions and expressions.
// Located at the end of the source for convinience
// Must finish with a 0
//
long (WINAPI * ConditionJumps[])(LPRDATA rdPtr, long param1, long param2) = 
{ 
	CND_SelectFirst,
	CND_SelectHighestAltV,
	CND_SelectLowestAltV,
	CND_SelectLast,
	CND_SelectAll,
	CND_SelectFrontmost,
	CND_SelectRearmost,
	CND_DiscardFirst,
	CND_DiscardLast,
	CND_CompareSelected,
	0, //CND_SelectRandom,
	0, //CND_DiscardRandom,
	0, //CND_SelectTiedHighestAltV,
	0, //CND_SelectTiedLowestAltV,
	CND_SelectIndex,
	0
};
	
short (WINAPI * ActionJumps[])(LPRDATA rdPtr, long param1, long param2) =
{
	0
};

long (WINAPI * ExpressionJumps[])(LPRDATA rdPtr, long param) = 
{     
	EXP_GetSelectedByName,
	EXP_GetSelectedByFixed,
	EXP_GetNameByFixed,
	0
};
