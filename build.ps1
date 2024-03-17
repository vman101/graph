$CC = "gcc"
$CFLAGS = "-Wall"
$TARGET = "out"
$SRC = "test.c"
$OBJ = "test.o"
$OBJDIR = "objs"

# Build the target
function Build-Target {
    Write-Host "Building target $TARGET..."
    & $CC $CFLAGS "$OBJDIR/$OBJ" -o $TARGET
}

# Compile the source file
function Compile-Source {
    Write-Host "Compiling source file $SRC..."
    & $CC $CFLAGS -c $SRC -o "$OBJDIR/$OBJ"
}

# Create the object directory if it doesn't exist
function Create-Object-Directory {
    if (-not (Test-Path $OBJDIR)) {
        Write-Host "Creating object directory $OBJDIR..."
        New-Item -ItemType Directory -Path $OBJDIR | Out-Null
    }
}

# Clean the project
function Clean-Project {
    Write-Host "Cleaning the project..."
    Remove-Item -Recurse -Force $OBJDIR, $TARGET -ErrorAction SilentlyContinue
}

# Main function
function Main {
    Create-Object-Directory
    Compile-Source
    Build-Target
}

# Execute main function
Main
