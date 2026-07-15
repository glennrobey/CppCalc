import { useState } from "react";

function App() {
  const [expression, setExpression] = useState("");
  const [result, setResult] = useState("");

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
    } catch (error) {
      setResult("Server connection failed");
    }
  }

  return (
    <div>
      <h1>C++ Smart Calculator</h1>

      <input
        value={expression}
        onChange={(e) => setExpression(e.target.value)}
        placeholder="Enter expression"
      />

      <button onClick={calculate}>Calculate</button>

      <h2>Result: {result}</h2>
    </div>
  );
}

export default App;
