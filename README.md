<div align="center">
  <h3 align="center">GuiClass</h3>

  <p align="center">
    A reimplementation of ReClass in C++ using ImGui.
    <br />
    <br />
    <a href="https://github.com/BenMcAvoy/GuiClass/releases">Releases</a>
    <a href="https://github.com/BenMcAvoy/GuiClass/issues">Report Bugs</a>
    <a href="https://github.com/BenMcAvoy/GuiClass/issues">Request Features</a>
  </p>
</div>

## Development
Download the repository recursively, e.g:
`git clone https://github.com/BenMcAvoy/GuiClass --recurse-submodules`

Build with cmake and make:
```bash
mkdir build
cmake -B ./build/ .
cd build && make
```

## Configured workflows
All the configured workflows:
- Todo issue management, if `// TODO: ` notices are detected in code, issues will be made on GitHub automatically.
