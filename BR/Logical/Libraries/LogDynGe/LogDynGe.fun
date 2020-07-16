(********************************************************************
 * COPYRIGHT -- KRONES AG
 ********************************************************************
 * Library: LogDynGe
 * File: LogDynGe.fun
 * Author: k1008014
 * Created: April 18, 2019
 ********************************************************************
 * Functions and function blocks of library LogDynGe
 ********************************************************************)

FUNCTION_BLOCK LogicDynamicGate
	VAR_INPUT
		InitLearn : BOOL;
		Params : LogDynConfiguration;
		ConstArray : ARRAY[0..25] OF DINT;
		VarPointerArray : ARRAY[0..25] OF DINT;
		Enable : BOOL;
	END_VAR
	VAR_OUTPUT
		OUT_Result : USINT;
		ErrorCode : INT;
	END_VAR
	VAR
		Ptrs : ARRAY[0..25] OF UDINT;
		PtrsTyp : ARRAY[0..25] OF USINT;
		Step : DINT;
		PosEdge : BOOL;
		LearnEdge : R_TRIG;
	END_VAR
END_FUNCTION_BLOCK

FUNCTION_BLOCK LT_fub
	VAR_OUTPUT
		out : BOOL;
	END_VAR
	VAR
		a : DINT;
		b : DINT;
	END_VAR
END_FUNCTION_BLOCK

FUNCTION_BLOCK GT_fub
	VAR_OUTPUT
		out : BOOL;
	END_VAR
	VAR
		a : DINT;
		b : DINT;
	END_VAR
END_FUNCTION_BLOCK

FUNCTION_BLOCK OR_fub
	VAR_OUTPUT
		out : BOOL;
	END_VAR
	VAR
		a : DINT;
		b : DINT;
	END_VAR
END_FUNCTION_BLOCK

FUNCTION_BLOCK NOT_fub
	VAR_OUTPUT
		out : BOOL;
	END_VAR
	VAR
		a : DINT;
	END_VAR
END_FUNCTION_BLOCK

FUNCTION_BLOCK AND_fub
	VAR_OUTPUT
		out : BOOL;
	END_VAR
	VAR
		a : DINT;
		b : DINT;
	END_VAR
END_FUNCTION_BLOCK

FUNCTION_BLOCK OUT_fub
	VAR_OUTPUT
		out : BOOL;
	END_VAR
	VAR
		a : DINT;
	END_VAR
END_FUNCTION_BLOCK

FUNCTION_BLOCK VAR_fub (* *) (*$GROUP=User*)
	VAR_INPUT
		n : DINT;
	END_VAR
	VAR_OUTPUT
		out : DINT;
	END_VAR
END_FUNCTION_BLOCK

FUNCTION_BLOCK BOL_fub (* *) (*$GROUP=User*)
	VAR_INPUT
		n : DINT;
	END_VAR
	VAR_OUTPUT
		out : BOOL;
	END_VAR
END_FUNCTION_BLOCK
