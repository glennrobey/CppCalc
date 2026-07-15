import { useState } from "react";

function App() {
  const [expression, setExpression] = useState("");
  const [result, setResult] = useState("");
  const [commandInput, setCommandInput] = useState("");
  const [showCommands, setShowCommands] = useState(false);

  const buttons = [
    "7",
    "8",
    "9",
    "/",
    "4",
    "5",
    "6",
    "*",
    "1",
    "2",
    "3",
    "-",
    "CMD",
    "0",
    ".",
    "+",
    "ENTER",
  ];

  async function calculate() {
    try {
      const response = await fetch("http://localhost:8080/calculate", {
        method: "POST",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify({
          expression,
        }),
      });

      const data = await response.json();

      if (data.result !== undefined) {
        setResult(data.result);
      } else {
        setResult(data.error);
      }
    } catch {
      setResult("Server connection failed");
    }
  }

  function handleButtonClick(button: string) {
    if (button === "CMD") {
      setShowCommands(!showCommands);
      return;
    }

    if (button === "ENTER") {
      calculate();
      return;
    }

    setExpression(expression + button);
  }

  return (
    <div className="min-h-screen bg-slate-950 text-slate-100 flex items-center justify-center">
      <div
        className="
          w-96
          rounded-xl
          border
          border-cyan-400
          bg-slate-900
          p-6
          shadow-lg
        "
      >
        {/* Terminal header */}
        <div className="mb-4 text-sm text-cyan-400 font-mono">
          cppcalc@localhost:~
        </div>

        {/* Calculator display */}
        <div
          className="
            mb-4
            rounded-lg
            border
            border-cyan-400
            bg-slate-950
            p-4
            font-mono
          "
        >
          <div className="text-right text-cyan-400 text-xl">
            {expression || "0"}
          </div>

          <div className="text-right text-slate-100 text-3xl">{result}</div>
        </div>

        {/* Keypad */}
        <div className="grid grid-cols-4 gap-3">
          {buttons.map((button) => (
            <button
              key={button}
              onClick={() => handleButtonClick(button)}
              className="
                rounded-lg
                bg-slate-800
                p-4
                text-xl
                font-mono
                hover:bg-blue-600
                transition
              "
            >
              {button}
            </button>
          ))}
        </div>

        {/* Command menu */}
        {showCommands && (
          <div
            className="
              mt-4
              rounded-lg
              border
              border-cyan-400
              p-4
              bg-slate-950
            "
          >
            <h2 className="mb-3 text-cyan-400 font-mono">Commands</h2>

            <div className="flex flex-col gap-2">
              <button
                className="
                  rounded
                  bg-slate-800
                  p-2
                  hover:bg-blue-600
                "
              >
                Variables
              </button>

              <button
                className="
                  rounded
                  bg-slate-800
                  p-2
                  hover:bg-blue-600
                "
              >
                History
              </button>

              <button
                className="
                  rounded
                  bg-slate-800
                  p-2
                  hover:bg-blue-600
                "
              >
                Clear
              </button>
            </div>
          </div>
        )}

        {/* Command input */}
        <input
          className="
            mt-4
            w-full
            rounded-lg
            border
            border-cyan-400
            bg-slate-950
            p-3
            font-mono
            text-cyan-400
            outline-none
            placeholder:text-slate-500
          "
          placeholder="calc> type command or expression"
          value={commandInput}
          onChange={(e) => setCommandInput(e.target.value)}
        />
      </div>
    </div>
  );
}

export default App;
