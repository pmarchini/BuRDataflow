(********************************************************************
 * COPYRIGHT -- KRONES AG
 ********************************************************************
 * File: Global.typ
 * Author: k1008014
 * Created: April 18, 2019
 ********************************************************************
 * Global data types of project ApcStruct
 ********************************************************************)

TYPE
	LogDynConfiguration_g : 	STRUCT 
		Format_NodeTyp : ARRAY[0..25]OF USINT;
		Format_I_1_typ : ARRAY[0..25]OF USINT;
		Format_I_1_ref : ARRAY[0..25]OF USINT;
		Format_I_2_typ : ARRAY[0..25]OF USINT;
		Format_I_2_ref : ARRAY[0..25]OF USINT;
	END_STRUCT;
END_TYPE
