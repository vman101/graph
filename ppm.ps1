function Read-PPM {
    param (
        [string]$FilePath
    )

    $stream = [System.IO.File]::OpenRead($FilePath)

    # Read magic number
    $magicNumber = [System.Text.Encoding]::ASCII.GetString(@([byte[]]::new(2)))
    $stream.Read($magicNumber, 0, 2) | Out-Null

    # Check if it's a P6 file
    if ($magicNumber -ne "P6") {
        Write-Host "Error: Not a valid P6 format PPM file."
        $stream.Close()
        return $null
    }

    # Read image dimensions
    $dimensions = @([byte[]]::new(2))
    $stream.Read($dimensions, 0, 2) | Out-Null
    $width = [BitConverter]::ToUInt16($dimensions, 0)
    $stream.Read($dimensions, 0, 2) | Out-Null
    $height = [BitConverter]::ToUInt16($dimensions, 0)

    # Read maximum color value
    $maxColor = @([byte[]]::new(1))
    $stream.Read($maxColor, 0, 1) | Out-Null

    # Read pixel data
    $pixelData = $stream.ReadAllBytes()

    $stream.Close()

    return @{
        Width = $width
        Height = $height
        MaxColor = $maxColor[0]
        PixelData = $pixelData
    }
}

function Display-PPM {
    param (
        [int]$Width,
        [int]$Height,
        [int]$MaxColor,
        [byte[]]$PixelData
    )

    $index = 0
    for ($y = 0; $y -lt $Height; $y++) {
        for ($x = 0; $x -lt $Width; $x++) {
            $r = $PixelData[$index]
            $g = $PixelData[$index + 1]
            $b = $PixelData[$index + 2]
            $index += 3

            $color = [System.Drawing.Color]::FromArgb(255, $r, $g, $b)
            $consoleColor = [System.Console]::BackgroundColor = $color
            Write-Host " " -NoNewline
        }
        Write-Host
    }
}

# Usage example
$imageData = Read-PPM -FilePath "C:\Users\victo\OneDrive\Dokumente\code\graph\img.ppm"
if ($imageData) {
    Display-PPM -Width $imageData.Width -Height $imageData.Height -MaxColor $imageData.MaxColor -PixelData $imageData.PixelData
}

