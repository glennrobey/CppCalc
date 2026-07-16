import { useEffect, useRef, useState } from "react";

function App() {
  const [expression, setExpression] = useState("");
  const [result, setResult] = useState("");
  const [commandInput, setCommandInput] = useState("");
  const [showCommands, setShowCommands] = useState(false);
  const [commandHistory, setCommandHistory] = useState<string[]>([]);
  const [historyIndex, setHistoryIndex] = useState(-1);
  const [terminalOutput, setTerminalOutput] = useState<string[]>([
    "Welcome to C++Calc!",
    "Type 'help' for commands.",
  ]);

  const terminalEndRef = useRef<HTMLDivElement>(null);

  useEffect(() => {
    terminalEndRef.current?.scrollIntoView({
      behavior: "smooth",
    });
  }, [terminalOutput]);
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

  async function runCommand(command = commandInput) {
    if (!command.trim()) return;

    setCommandHistory((prev) => [...prev, command]);
    setHistoryIndex(-1);

    try {
      const response = await fetch("http://localhost:8080/calculate", {
        method: "POST",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify({
          expression: command,
        }),
      });

      const data = await response.json();

      if (data.result !== undefined) {
        setResult(data.result);

        setTerminalOutput((prev) => [
          ...prev,
          `> ${command}`,
          String(data.result),
        ]);
      } else {
        setResult(data.error);

        setTerminalOutput((prev) => [
          ...prev,
          `> ${command}`,
          String(data.error),
        ]);
      }

      setCommandInput("");
    } catch {
      setCommandInput("");
      setResult("Server connection failed");

      setTerminalOutput((prev) => [
        ...prev,
        `> ${commandInput}`,
        "Server connection failed",
      ]);
    }
  }

  useEffect(() => {
    function handleKeyboard(event: KeyboardEvent) {
      const key = event.key;

      if ("0123456789+-*/.".includes(key)) {
        setExpression((prev) => prev + key);
      }

      if (key === "Backspace") {
        setExpression((prev) => prev.slice(0, -1));
      }

      if (key === "Escape") {
        setExpression("");
        setResult("");
        setCommandInput("");
      }
    }

    window.addEventListener("keydown", handleKeyboard);

    return () => {
      window.removeEventListener("keydown", handleKeyboard);
    };
  }, [commandInput]);

  function handleButtonClick(button: string) {
    if (button === "CMD") {
      setShowCommands(!showCommands);
      return;
    }

    if (button === "ENTER") {
      calculate();
      return;
    }

    setExpression((prev) => prev + button);
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
          c++calc@localhost:~
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
                onClick={() => runCommand("vars")}
                className="rounded bg-slate-800 p-2 hover:bg-blue-600"
              >
                Variables
              </button>

              <button
                onClick={() => runCommand("history")}
                className="rounded bg-slate-800 p-2 hover:bg-blue-600"
              >
                History
              </button>

              <button
                onClick={() => runCommand("clear")}
                className="rounded bg-slate-800 p-2 hover:bg-blue-600"
              >
                Clear
              </button>
            </div>
          </div>
        )}

        {/* Terminal output */}
        <div
          className="
    mt-4
    h-48
    overflow-y-auto
    rounded-lg
    border
    border-cyan-400
    bg-slate-950
    p-3
    font-mono
    text-cyan-400
    whitespace-pre-wrap
  "
        >
          {terminalOutput.map((line, index) => (
            <div key={index}>{line}</div>
          ))}

          <div ref={terminalEndRef} />
        </div>

        {/* Command input */}
        <div
          className="
    mt-4
    flex
    items-center
    rounded-lg
    border
    border-cyan-400
    bg-slate-950
    p-3
  "
        >
          <span className="text-cyan-400 font-mono">&gt;</span>

          <input
            className="
              ml-2
              flex-1
              bg-transparent
              font-mono
              text-cyan-400
              outline-none
            "
            placeholder="type help for commands"
            value={commandInput}
            onChange={(e) => setCommandInput(e.target.value)}
            onKeyDown={(e) => {
              if (e.key === "Enter") {
                runCommand();
              }

              if (e.key === "ArrowUp") {
                e.preventDefault();

                if (commandHistory.length === 0) return;

                const newIndex =
                  historyIndex === -1
                    ? commandHistory.length - 1
                    : Math.max(historyIndex - 1, 0);

                setHistoryIndex(newIndex);
                setCommandInput(commandHistory[newIndex]);
              }

              if (e.key === "ArrowDown") {
                e.preventDefault();

                if (commandHistory.length === 0) return;

                const newIndex = historyIndex + 1;

                if (newIndex >= commandHistory.length) {
                  setHistoryIndex(-1);
                  setCommandInput("");
                  return;
                }

                setHistoryIndex(newIndex);
                setCommandInput(commmandHistory[newIndex]);
              }
            }}
          />
        </div>
      </div>
    </div>
  );
}

export default App;
