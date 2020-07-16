/********************************************************************
 * COPYRIGHT -- KRONES AG
 ********************************************************************
 * Library: LogDynGe
 * File: LogDynGe.c
 * Author: k1008014
 * Created: April 18, 2019
 ********************************************************************
 * Implementation of library LogDynGe
 ********************************************************************/

#include <bur/plctypes.h>
#include <AsDefault.h>
#include <sys_lib.h>
#include <standard.h>
#include <string.h>

#define LT  		1
#define GT  		2
#define OR  		3
#define NOT 		4
#define AND 		5
#define OUT 		6
/* K1008014 -> patch 0.0.2 -> 26/04/2019 # BEG */
#define VAR 		7
#define BOL 		8
/*TODO				*/
#define CONSTVAR 	9
#define CONSTBOL	10	 	 
/* K1008014 -> patch 0.0.2 -> 26/04/2019 # END */
/* K1008014 -> patch 0.0.3 -> 29/04/2019 # BEG */
#define _TON			11
#define _TOF			12
/* K1008014 -> patch 0.0.3 -> 29/04/2019 # END */

//Errors code
#define ERR_OK 0;
#define ALLOC_ERROR 1;
#define DEALLOC_ERROR 2;


#define _MAX_N_NODES 25

#ifdef __cplusplus
	extern "C"
	{
#endif

#include "LogDynGe.h"

#ifdef __cplusplus
	};
#endif

/*Parser*/

/*1111|11|1111|11|1111 */
/*typ |t1| v1 |t2| v2  */

#define _TYP 1
#define _T1 2
#define _V1 3
#define _T2 4
#define _V2 5

INT Parse(INT cmd,USINT element)
{
	switch(element)
	{
		case _TYP:
			return ((cmd >> 12) & 0x40);
		
		case _T1:
			return ((cmd >> 10) & 0x2);
		
		case _V1:
			return ((cmd >> 6) & 0x40);
		
		case _T2:
			return ((cmd >> 4) & 0x2);
		
		case _V2:
			return (cmd & 0x40);
		
		default:
			return -1;
	}
}


USINT MemClear(struct LogicDynamicGate* inst)
{
	int i;
	int size;
	
	for(i = 0;i < _MAX_N_NODES; i++) 
	{
		switch(inst->PtrsTyp[i])
		{
			case LT:
				size = sizeof(struct LT_fub);
				break;
			case GT:
				size = sizeof(struct GT_fub);
				break;
		
			case OR:
				size = sizeof(struct OR_fub);
				break;
		
			case NOT:
				size = sizeof(struct NOT_fub);
				break;
		
			case AND:
				size = sizeof(struct AND_fub);
				break;
			
			case OUT:
				size = sizeof(struct OUT_fub);
				break;
			
			case VAR:
				size = sizeof(struct VAR_fub);
				break;
			
			case BOL:
				size = sizeof(struct BOL_fub);
				break;
		}
		
		if(inst->Ptrs[i] != 0 && inst->PtrsTyp[i] != 0)
		{
			if(TMP_free(size,(void**)inst->Ptrs[i]) != 0 ) { inst->ErrorCode = DEALLOC_ERROR; }	
			inst->Ptrs[i] = 0;
		}
	}
}

USINT MemAllocNodes(struct LogicDynamicGate* inst)
{
	int i;
	
	MemClear(inst);
	
	memcpy(
		(UDINT)(void*)inst->PtrsTyp,
		(UDINT)(void*)inst->Params.Format_NodeTyp,
		sizeof(inst->Params.Format_NodeTyp)
		);

	
	for(i = 0;i < _MAX_N_NODES; i++)
	{
		
		switch(inst->Params.Format_NodeTyp[i])
		{
			case LT:
				/*if(inst->Ptrs[i] != 0)
				{
					if(TMP_free(sizeof(LT_fub),(void**)inst->Ptrs[i]) != 0 ) { inst->ErrorCode = DEALLOC_ERROR; }
				}*/
				if( (TMP_alloc(sizeof(struct LT_fub), (void**)&inst->Ptrs[i])) != 0 ){ inst->ErrorCode = ALLOC_ERROR; }
				break;
		
			case GT:
				/*if(inst->Ptrs[i] != 0)
				{
					if(TMP_free(sizeof(GT_fub),(void**)inst->Ptrs[i]) != 0 ) { inst->ErrorCode = DEALLOC_ERROR; }
				}*/
				if( (TMP_alloc(sizeof(struct GT_fub), (void**)&inst->Ptrs[i])) != 0 ){ inst->ErrorCode = ALLOC_ERROR; }
				break;
		
			case OR:
				/*if(inst->Ptrs[i] != 0)
				{
					if(TMP_free(sizeof(OR_fub),(void**)inst->Ptrs[i]) != 0 ) { inst->ErrorCode = DEALLOC_ERROR; }
				}*/
				if( (TMP_alloc(sizeof(struct OR_fub), (void**)&inst->Ptrs[i])) != 0 ){ inst->ErrorCode = ALLOC_ERROR; }
				break;
		
			case NOT:
				/*if(inst->Ptrs[i] != 0)
				{
					if(TMP_free(sizeof(NOT_fub),(void**)inst->Ptrs[i]) != 0 ) { inst->ErrorCode = DEALLOC_ERROR; }
				}*/
				if( (TMP_alloc(sizeof(struct NOT_fub), (void**)&inst->Ptrs[i])) != 0 ){ inst->ErrorCode = ALLOC_ERROR; }
				break;
		
			case AND:
				/*if(inst->Ptrs[i] != 0)
				{
					if(TMP_free(sizeof(AND_fub),(void**)inst->Ptrs[i]) != 0 ) { inst->ErrorCode = DEALLOC_ERROR; }
				}*/
				if( (TMP_alloc(sizeof(struct AND_fub), (void**)&inst->Ptrs[i])) != 0 ){ inst->ErrorCode = ALLOC_ERROR; }
				break;
			
			case OUT:
				/*if(inst->Ptrs[i] != 0)
				{
					if(TMP_free(sizeof(OUT_fub),(void**)inst->Ptrs[i]) != 0 ) { inst->ErrorCode = DEALLOC_ERROR; }
				}*/
				if( (TMP_alloc(sizeof(struct OUT_fub), (void**)&inst->Ptrs[i])) != 0 ){ inst->ErrorCode = ALLOC_ERROR; }
				break;
			
			case VAR:
				/*if(inst->Ptrs[i] != 0)
				{
					if(TMP_free(sizeof(VAR_fub),(void**)inst->Ptrs[i]) != 0 ) { inst->ErrorCode = DEALLOC_ERROR; }
				}*/
				if( (TMP_alloc(sizeof(struct VAR_fub), (void**)&inst->Ptrs[i])) != 0 ){ inst->ErrorCode = ALLOC_ERROR; }
				break;
			
			case BOL:
				/*if(inst->Ptrs[i] != 0)
				{
					if(TMP_free(sizeof(BOL_fub),(void**)inst->Ptrs[i]) != 0 ) { inst->ErrorCode = DEALLOC_ERROR; }
				}*/
				if( (TMP_alloc(sizeof(struct BOL_fub), (void**)&inst->Ptrs[i])) != 0 ){ inst->ErrorCode = ALLOC_ERROR; }
				break;
		
			default:
				break;	
			
		}
	}
	
	return inst->ErrorCode;
}


UDINT getInputVarPointer(struct LogicDynamicGate* inst, int VarGateNumber)
{
	return (UDINT)(void*)inst->VarPointerArray[VarGateNumber];
}

UDINT getNodeOutPointer(struct LogicDynamicGate* inst, int NodeNumber)
{
	if(NodeNumber > _MAX_N_NODES) { return 0; }
	
	
	UDINT ptr;
	struct LT_fub* 	LT_ptr;  
	struct GT_fub* 	GT_ptr;
	struct OR_fub* 	OR_ptr;
	struct NOT_fub*	NOT_ptr;
	struct AND_fub* AND_ptr;
	struct VAR_fub* VAR_ptr;
	struct BOL_fub* BOL_ptr;
	//struct TON* TON_ptr;
	//struct TOF* TOF_ptr;
	
	switch(inst->Params.Format_NodeTyp[NodeNumber])
	{	
		case LT:
			LT_ptr = inst->Ptrs[NodeNumber];
			ptr = (UDINT)(void*)&(LT_ptr->out);
			break;
		
		case GT:
			GT_ptr = inst->Ptrs[NodeNumber];
			ptr = (UDINT)(void*)&(GT_ptr->out);
			break;
		
		case OR:
			OR_ptr = inst->Ptrs[NodeNumber];
			ptr = (UDINT)(void*)&(OR_ptr->out);
			break;
		
		case NOT:
			NOT_ptr = inst->Ptrs[NodeNumber];
			ptr = (UDINT)(void*)&(NOT_ptr->out);
			break;
		
		case AND:
			AND_ptr = inst->Ptrs[NodeNumber];
			ptr = (UDINT)(void*)&(AND_ptr->out);
			break;
		
		case VAR:
			VAR_ptr = inst->Ptrs[NodeNumber];
			ptr = (UDINT)(void*)&(VAR_ptr->out);
			break;
		
		case BOL:
			BOL_ptr = inst->Ptrs[NodeNumber];
			ptr = (UDINT)(void*)&(BOL_ptr->out);
			break;
		
		case _TON:
			//TODO
			break;
		
		case _TOF:
			//TODO
			break;
			
		
		default:
			break;
	}
	return ptr;
}


void refreshLogic(struct LogicDynamicGate* inst)
{
	struct OUT_fub* OUT_ptr;
	int i = 0;
	
	for(i = 0; i < _MAX_N_NODES; i++)
	{
		switch(inst->Params.Format_NodeTyp[i])
		{
			case LT:
				LT_fub(inst->Ptrs[i]);
				break;
			
			case GT:
				GT_fub(inst->Ptrs[i]);
				break;
			
			case OR:
				OR_fub(inst->Ptrs[i]);
				break;
			
			case NOT:
				NOT_fub(inst->Ptrs[i]);
				break;
			
			case AND:
				AND_fub(inst->Ptrs[i]);
				break;
			
			/*FUN OUTPUT*/
			case OUT:
				OUT_fub(inst->Ptrs[i]);
				OUT_ptr = inst->Ptrs[i];
				inst->OUT_Result = OUT_ptr->out;
				break;
			
			case VAR:
				VAR_fub(inst->Ptrs[i]);
				break;
			
			case BOL:
				BOL_fub(inst->Ptrs[i]);
				break;
			
			default:
				break;
		}
	}
}


#define _NODE  0
#define _VAR   1
#define _CONST 2

/*
LOGIC

 0,0,0,0,0,0,0,0,0,0,0,0,0,0 -> tipo nodo
 0,0,0,0,0,0,0,0,0,0,0,0,0,0 -> ingresso 1 tipo uscita nodo / Variabile -> 1 = variabile, 0 = nodo , 2 -> valore costante
 0,0,0,0,0,0,0,0,0,0,0,0,0,0 -> ingresso 1 numerico nodo/variabile
 0,0,0,0,0,0,0,0,0,0,0,0,0,0 -> ingresso 2 tipo uscita nodo / Variabile -> 1 = variabile, 0 = nodo , 2 -> valore costante
 0,0,0,0,0,0,0,0,0,0,0,0,0,0 -> ingresso 2 numerico nodo/variabile

EXAMPLE

 AND,AND,LT    ,NOT,0,0,0,0,0,0
 1  ,0  ,2     ,0  ,0,0,0,0,0,0
 1  ,1  ,100   ,3  ,0,0,0,0,0,0
 1  ,1  ,1     ,0  ,0,0,0,0,0,0
 1  ,2  ,2     ,0  ,0,0,0,0,0,0
*/
void setLogic(struct LogicDynamicGate* inst)
{
	int i = 0;
	
	struct LT_fub* 	LT_ptr;  
	
	struct GT_fub* 	GT_ptr;
	
	struct OR_fub* 	OR_ptr;
	
	struct NOT_fub*	NOT_ptr;
	
	struct AND_fub* AND_ptr;
	
	struct OUT_fub* OUT_ptr;
	
	struct VAR_fub* VAR_ptr;
	
	struct BOL_fub* BOL_ptr;
	
	for(i=0; i < _MAX_N_NODES; i++)
	{
		//per prendere valore da nodo differente :  //LT_ptr->a = getNodeOutPointer(inst,2);
		switch(inst->Params.Format_NodeTyp[i])
		{
			case LT:
				LT_ptr	 	= inst->Ptrs[i];
				/*Input 1*/
				if(inst->Params.Format_I_1_typ[i] == _NODE) {LT_ptr->a = getNodeOutPointer(inst, inst->Params.Format_I_1_ref[i]);}
				if(inst->Params.Format_I_1_typ[i] == _VAR)  {LT_ptr->a = getInputVarPointer(inst, inst->Params.Format_I_1_ref[i]);}
				/*Input 2*/
				if(inst->Params.Format_I_2_typ[i] == _NODE) {LT_ptr->b = getNodeOutPointer(inst, inst->Params.Format_I_2_ref[i]);}
				if(inst->Params.Format_I_2_typ[i] == _VAR)  {LT_ptr->b = getInputVarPointer(inst, inst->Params.Format_I_2_ref[i]);}
				break;
			
			case GT:
				GT_ptr	 	= inst->Ptrs[i];
				/*Input 1*/
				if(inst->Params.Format_I_1_typ[i] == _NODE) {GT_ptr->a = getNodeOutPointer(inst, inst->Params.Format_I_1_ref[i]);}
				if(inst->Params.Format_I_1_typ[i] == _VAR)  {GT_ptr->a = getInputVarPointer(inst, inst->Params.Format_I_1_ref[i]);}
				/*Input 2*/
				if(inst->Params.Format_I_2_typ[i] == _NODE) {GT_ptr->b = getNodeOutPointer(inst, inst->Params.Format_I_2_ref[i]);}
				if(inst->Params.Format_I_2_typ[i] == _VAR)  {GT_ptr->b = getInputVarPointer(inst, inst->Params.Format_I_2_ref[i]);}
				break;
			
			case OR:
				OR_ptr	 	= inst->Ptrs[i];
				/*Input 1*/
				if(inst->Params.Format_I_1_typ[i] == _NODE) {OR_ptr->a = getNodeOutPointer(inst, inst->Params.Format_I_1_ref[i]);}
				if(inst->Params.Format_I_1_typ[i] == _VAR)  {OR_ptr->a = getInputVarPointer(inst, inst->Params.Format_I_1_ref[i]);}
				/*Input 2*/
				if(inst->Params.Format_I_2_typ[i] == _NODE) {OR_ptr->b = getNodeOutPointer(inst, inst->Params.Format_I_2_ref[i]);}
				if(inst->Params.Format_I_2_typ[i] == _VAR)  {OR_ptr->b = getInputVarPointer(inst, inst->Params.Format_I_2_ref[i]);}
				break;
			
			case NOT:
				NOT_ptr	 	= inst->Ptrs[i];
				if(inst->Params.Format_I_1_typ[i] == _NODE) {NOT_ptr->a = getNodeOutPointer(inst, inst->Params.Format_I_1_ref[i]);}
				if(inst->Params.Format_I_1_typ[i] == _VAR)  {NOT_ptr->a = getInputVarPointer(inst, inst->Params.Format_I_1_ref[i]);}
				break;
			
			case AND:
				AND_ptr	 	= inst->Ptrs[i];
				/*Input 1*/
				if(inst->Params.Format_I_1_typ[i] == _NODE) {AND_ptr->a = getNodeOutPointer(inst, inst->Params.Format_I_1_ref[i]);}
				if(inst->Params.Format_I_1_typ[i] == _VAR)  {AND_ptr->a = getInputVarPointer(inst, inst->Params.Format_I_1_ref[i]);}
				/*Input 2*/
				if(inst->Params.Format_I_2_typ[i] == _NODE) {AND_ptr->b = getNodeOutPointer(inst, inst->Params.Format_I_2_ref[i]);}
				if(inst->Params.Format_I_2_typ[i] == _VAR)  {AND_ptr->b = getInputVarPointer(inst, inst->Params.Format_I_2_ref[i]);}
				break;
			
			case OUT:
				OUT_ptr	 	= inst->Ptrs[i];
				if(inst->Params.Format_I_1_typ[i] == _NODE) {OUT_ptr->a = getNodeOutPointer(inst, inst->Params.Format_I_1_ref[i]);}
				if(inst->Params.Format_I_1_typ[i] == _VAR)  {OUT_ptr->a = getInputVarPointer(inst, inst->Params.Format_I_1_ref[i]);}
				break;
			
			case VAR:
				VAR_ptr	 	= inst->Ptrs[i];
				if(inst->Params.Format_I_1_typ[i] == _NODE) {VAR_ptr->n = getNodeOutPointer(inst, inst->Params.Format_I_1_ref[i]);}
				if(inst->Params.Format_I_1_typ[i] == _VAR)  {VAR_ptr->n = getInputVarPointer(inst, inst->Params.Format_I_1_ref[i]);}
				break;
			
			case BOL:
				BOL_ptr	 	= inst->Ptrs[i];
				if(inst->Params.Format_I_1_typ[i] == _NODE) {BOL_ptr->n = getNodeOutPointer(inst, inst->Params.Format_I_1_ref[i]);}
				if(inst->Params.Format_I_1_typ[i] == _VAR)  {BOL_ptr->n = getInputVarPointer(inst, inst->Params.Format_I_1_ref[i]);}
				break;
			
			default:
				break;
		}
	}
}

//Step
#define INIT_RAM   		 	0
#define INIT_LOGIC		 	1
#define PRE_OPERATIONAL		2
#define OPERATIONAL			3	

void LogicDynamicGate(struct LogicDynamicGate* inst)
{
	
	inst->LearnEdge.CLK = inst->InitLearn;
	R_TRIG(&inst->LearnEdge);
	
	if(!inst->PosEdge || inst->LearnEdge.Q)
	{ 
		inst->Step = INIT_RAM;
		inst->PosEdge = 1;
		inst->InitLearn = 0; //Verificare
	}
	
	switch(inst->Step)
	{
		case INIT_RAM:
			MemAllocNodes(inst);
			if(inst->ErrorCode == 0)
			{
				inst->Step = INIT_LOGIC;
			}
			break;
		
		case INIT_LOGIC:
			setLogic(inst);
			if(inst->ErrorCode == 0)
			{
				inst->Step = PRE_OPERATIONAL;
			}
			break;
		
		case PRE_OPERATIONAL:
			if(inst->Enable)
			{
				inst->Step = OPERATIONAL;	
			}
			break;
		
		case OPERATIONAL:
			if(!inst->Enable)
			{
				inst->Step = PRE_OPERATIONAL;	
			}
			refreshLogic(inst);
			break;
	}
	
//	if(!inst->PosEdge)
//	{
//		MemAllocNodes(inst);
//		inst->PosEdge = 1;
//		
//		switch
//	}else
//	{
//		if(inst->InitLearn)
//		{
//			setLogic(inst);
//			inst->InitLearn = 0;
//		}
//		if(inst->Enable)
//		{
//			refreshLogic(inst);
//		}
//	}
	
}



//FUB BLOCKS

//LT
void LT_fub(struct LT_fub* inst)
{
	if(inst->a != 0 && inst->b != 0)
	{
		DINT *ptr_a = inst->a;
		DINT *ptr_b = inst->b;
		inst->out = *ptr_a < *ptr_b;	
	}
}

//GT
void GT_fub(struct GT_fub* inst)
{
	if(inst->a != 0 && inst->b != 0)
	{
		DINT *ptr_a = inst->a;
		DINT *ptr_b = inst->b;
		inst->out = *ptr_a >= *ptr_b;
	}
}

//OR
void OR_fub(struct OR_fub* inst)
{
	if(inst->a != 0 && inst->b != 0)
	{
		BOOL *ptr_a = inst->a;
		BOOL *ptr_b = inst->b;
		inst->out = *ptr_a || *ptr_b;
	}
}

//NOT
void NOT_fub(struct NOT_fub* inst)
{
	if(inst->a != 0)
	{	
		BOOL *ptr = inst->a;
		inst->out = !(*ptr);
	}
}

//AND
void AND_fub(struct AND_fub* inst)
{
	if(inst->a != 0 && inst->b != 0)
	{
		BOOL *ptr_a = inst->a;
		BOOL *ptr_b = inst->b;
		inst->out = *ptr_a && *ptr_b;
	}
}

//OUT
void OUT_fub(struct OUT_fub* inst)
{
	if(inst->a != 0)
	{
		BOOL *ptr = inst->a;
		inst->out = *ptr > 0;
	}
}

/* K1008014 -> patch 0.0.2 -> 26/04/2019 # BEG */

//VAR
void VAR_fub(struct VAR_fub* inst)
{
	if(inst->n != 0) 
	{
		DINT *ptr = inst->n;
		inst->out = *ptr;	
	}
}

//BOL
void BOL_fub(struct BOL_fub* inst)
{
	if(inst->n != 0) 
	{
		BOOL *ptr = inst->n;
		inst->out = *ptr;	
	}
}

/* K1008014 -> patch 0.0.2 -> 26/04/2019 # END */