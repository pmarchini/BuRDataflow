using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using NodeEditor;

namespace SignalLogicGenerator
{
    // Main context of the sample, each
    // method corresponds to a node by attribute decoration
    public class LogicalContext : INodesContext
    {
        public NodeVisual CurrentProcessingNode { get; set; }
        public event Action<string, NodeVisual, FeedbackType, object, bool> FeedbackInfo;

        [Node("LT", "Input", "Basic", "Allows to output a simple value.", false, 1)]
        public void LT(float a, float b, out bool outValue)
        {
            outValue = a < b;
        }

        [Node("GT", "Input", "Basic", "Allows to output a simple value.", false, 2)]
        public void GT(float a, float b, out bool outValue)
        {
            outValue = a >= b;
        }

        [Node("OR", "Input", "Basic", "Allows to output a simple value.", false, 3)]
        public void OrBlock(bool a, bool b, out bool outValue)
        {
            outValue = a || b;
        }

        [Node("NOT", "Input", "Basic", "Allows to output a simple value.", false, 4)]
        public void Not(bool input, out bool outValue)
        {
            outValue = !input;
        }

        [Node("AND", "Input", "Basic", "Allows to output a simple value.", false, 5)]
        public void AndBlock(bool a, bool b, out bool outValue)
        {
            outValue = a && b;
        }

        [Node("OUT", "Input", "Basic", "Allows to output a simple value.", false, 6)]
        public void OUT(bool input, out bool outValue)
        {
            outValue = input;
        }

        /*************TO BE ADDED*************/

        [Node("Var", "Variables", "Basic", "Allows to output a simple value.", false, 7)]
        public void Var(int n, out float outValue)
        {
            outValue = 1;
        }

        [Node("VarBool", "Variables", "Basic", "Allows to output a simple value.", false, 8)]
        public void VarBool(int n, out bool outValue)
        {
            outValue = true;
        }

        [Node("ValueConst", "Input", "Basic", "Allows to output a simple value.", false, 9)]
        public void ValueConst(float inValue, out float outValue)
        {
            outValue = inValue;
        }

        [Node("BooleanConst", "Input", "Basic", "Allows to output a simple value.", false, 10)]
        public void BooleanConst(bool inValue, out bool outValue)
        {
            outValue = inValue;
        }






    }
}
