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
    <div className="min-h-screen bg-black text-white flex items-center justify-center">
      <div className="w-96 rounded-xl border border-green-500 bg-zinc-900 p-6 shadow-lg">
        {/* Calculator display */}
        <div className="mb-4 rounded-lg bg-black border border-green-500 p-4">
          <div className="text-right text-green-400 text-xl">
            {expression || "0"}
          </div>

          <div className="text-right text-white text-3xl">{result}</div>
        </div>

        {/* Keypad */}
        <div className="grid grid-cols-4 gap-3">
          {buttons.map((button) => (
            <button
              key={button}
              onClick={() => handleButtonClick(button)}
              className="
                rounded-lg
                bg-zinc-800
                p-4
                text-xl
                hover:bg-green-600
                transition
              "
            >
              {button}
            </button>
          ))}
        </div>

        {/* Command menu */}
        {showCommands && (
          <div className="mt-4 rounded-lg border border-green-500 p-4">
            <h2 className="mb-3 text-green-400">Commands</h2>

            <div className="flex flex-col gap-2">
              <button className="rounded bg-zinc-800 p-2">Variables</button>

              <button className="rounded bg-zinc-800 p-2">History</button>

              <button className="rounded bg-zinc-800 p-2">Clear</button>
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
            border-green-500
            bg-black
            p-3
            text-green-400
            outline-none
          "
          placeholder="> type command or expression"
          value={commandInput}
          onChange={(e) => setCommandInput(e.target.value)}
        />
      </div>
    </div>
  );
}

export default App;
