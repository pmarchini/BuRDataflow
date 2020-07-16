(********************************************************************
 * COPYRIGHT -- KRONES AG
 ********************************************************************
 * Program: DynamicGateTest
 * File: DynamicGateTest.st
 * Author: k1008014
 * Created: April 21, 2019
 ********************************************************************
 * Implementation of program DynamicGateTest
 ********************************************************************)

PROGRAM _INIT
	
	DynamicGate_1_Par.Format_NodeTyp := LogicGate_Data_1;
	DynamicGate_1_Par.Format_I_1_typ := LogicGate_Data_2;
	DynamicGate_1_Par.Format_I_1_ref := LogicGate_Data_3;
	DynamicGate_1_Par.Format_I_2_typ := LogicGate_Data_4;
	DynamicGate_1_Par.Format_I_2_ref := LogicGate_Data_5;
	
	LogicDynamicGate_0.Params		 := DynamicGate_1_Par;
	LogicDynamicGate_0();
	
END_PROGRAM

PROGRAM _CYCLIC

	DownloadGateRecipe := DownloadGateRecipe;
	
	DynamicGate_1_Par.Format_NodeTyp := LogicGate_Data_1;
	DynamicGate_1_Par.Format_I_1_typ := LogicGate_Data_2;
	DynamicGate_1_Par.Format_I_1_ref := LogicGate_Data_3;
	DynamicGate_1_Par.Format_I_2_typ := LogicGate_Data_4;
	DynamicGate_1_Par.Format_I_2_ref := LogicGate_Data_5;
	
	LogicDynamicGate_0.Params		 		:= DynamicGate_1_Par;
	LogicDynamicGate_0.InitLearn	 		:= DownloadGateRecipe;
	LogicDynamicGate_0.VarPointerArray[0] 	:= ADR(Var_1); 
	LogicDynamicGate_0.VarPointerArray[1] 	:= ADR(Var_2); 
	LogicDynamicGate_0.VarPointerArray[2] 	:= ADR(Var_3);
	LogicDynamicGate_0.VarPointerArray[3] 	:= ADR(Var_4);
	LogicDynamicGate_0();

	IF DownloadGateRecipe THEN DownloadGateRecipe := FALSE; END_IF

END_PROGRAM
