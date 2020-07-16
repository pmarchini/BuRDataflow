(********************************************************************
 * COPYRIGHT -- KRONES AG
 ********************************************************************
 * Library: LogDynGe
 * File: LogDynGe.typ
 * Author: k1008014
 * Created: April 18, 2019
 ********************************************************************
 * Data types of library LogDynGe
 ********************************************************************)

TYPE
	LogDynConfiguration : 	STRUCT 
		Format_NodeTyp : ARRAY[0..25]OF USINT;
		Format_I_1_typ : ARRAY[0..25]OF USINT;
		Format_I_1_ref : ARRAY[0..25]OF USINT;
		Format_I_2_typ : ARRAY[0..25]OF USINT;
		Format_I_2_ref : ARRAY[0..25]OF USINT;
	END_STRUCT;
END_TYPE
