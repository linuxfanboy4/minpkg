# MinPkg - Minimal Package Manager

MinPkg is a lightweight and minimalistic package manager designed for simplicity and ease of use. It allows users to create, install, uninstall, list, and execute packages with minimal overhead. The tool is written in C and is intended for users who prefer a straightforward and efficient package management solution.

## Features

- **Create Packages**: Define custom packages with a URL and a command.
- **Install Packages**: Download and install packages from a specified URL.
- **Uninstall Packages**: Remove installed packages from the system.
- **List Installed Packages**: View all installed packages.
- **Execute Packages**: Run installed packages directly from the command line.

## Installation

To install MinPkg, use the following command:

```bash
wget https://raw.githubusercontent.com/linuxfanboy4/minpkg/refs/heads/main/src/minpkg.c -O minpkg.c && gcc minpkg.c -o minpkg && sudo mv minpkg /usr/local/bin/
```

This command downloads the source code, compiles it, and moves the executable to `/usr/local/bin/` for global access.

## Usage

MinPkg supports several commands to manage packages:

### Create a Package

To create a new package, use the `create` command followed by the URL, package name, and command:

```bash
minpkg create <url> <package_name> <command>
```

Example:

```bash
minpkg create https://example.com/script.sh myscript "bash script.sh"
```

This creates a package named `myscript.minpkg` in the `./packages/` directory.

### Install a Package

To install a package, use the `install` command followed by the package name:

```bash
minpkg install <package_name>
```

Example:

```bash
minpkg install myscript.minpkg
```

This downloads the package from the specified URL, makes it executable, and moves it to the `./packages/` directory.

### Uninstall a Package

To uninstall a package, use the `uninstall` command followed by the package name:

```bash
minpkg uninstall <package_name>
```

Example:

```bash
minpkg uninstall myscript.minpkg
```

This removes the specified package from the `./packages/` directory.

### List Installed Packages

To list all installed packages, use the `list` command:

```bash
minpkg list
```

This displays all packages currently installed in the `./packages/` directory.

### Execute a Package

To execute an installed package, use the `use` command followed by the package name:

```bash
minpkg use <package_name>
```

Example:

```bash
minpkg use myscript.minpkg
```

This runs the specified package as an executable.

## Directory Structure

- **./packages/**: Directory where all packages are stored.
- **./tmp/**: Temporary directory used during package installation.

## Error Handling

MinPkg includes basic error handling to notify users of issues such as:

- Failed package creation.
- Package not found during installation or execution.
- Failed downloads or installations.
- Failed uninstallations.

## Contributing

Contributions to MinPkg are welcome. Please follow these steps to contribute:

1. Fork the repository.
2. Create a new branch for your feature or bug fix.
3. Commit your changes.
4. Push your branch to your forked repository.
5. Submit a pull request with a detailed description of your changes.

## License

MinPkg is released under the MIT License. See the `LICENSE` file for more details.

## Support

For support or questions, please open an issue on the [GitHub repository](https://github.com/linuxfanboy4/minpkg).

---

MinPkg is designed to be a simple yet powerful tool for managing packages. Its minimalistic approach ensures that it remains lightweight and easy to use, making it an ideal choice for users who prefer efficiency and simplicity in their package management tools.
