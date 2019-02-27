#install script fo the bachendpart 
#load mysql assembly
Add-Type -Path "MySql.Data.dll"

Write-Output "Welcome to your UserManagement backend installation setup"

#setup db
Write-Output "database setup:"
#http://winrun4j.sourceforge.net/
#read parameters
$mysqlServer =  Read-Host -Prompt "mysql address default (localhost)" 

if ($mysqlServer -eq $null) {
    $mysqlServer = "localhost"
}

$mysqlPort = Read-Host -Prompt "mysql port default (3306)"

if ($mysqlPort -eq $null) {
    $mysqlPort = "3306"
}


$installUser =  Read-Host -Prompt "user" 

if ($installUser -eq $null){
    ThrowError -ExceptionMessage "empty user"
}

$installUserPW = Read-Host -AsSecureString  -Prompt "password"  

#workaround for getting the secure string, you cant currently use the cmdlet ConvertFrom-SecureString see https://github.com/PowerShell/PowerShell/issues/1654
$bstr = [System.Runtime.InteropServices.Marshal]::SecureStringToBSTR($installUserPW)
$installUserPWSTR = [System.Runtime.InteropServices.Marshal]::PtrToStringAuto($bstr)

#build connection
$connection = New-Object -TypeName MySql.Data.MySqlClient.MySqlConnection

Write-Output "SERVER=$mysqlServer;DATABASE=mysql;UID=$installUser;PWD=$installUserPWSTR"
$connection.ConnectionString = "SERVER=$mysqlServer;UID=$installUser;PWD=$installUserPWSTR"

$connection.Open()

#setup sql command
$sqlCommand = New-Object -TypeName MySql.Data.MySqlClient.MySqlCommand
$sql = Get-Content "test.sql"
$sqlCommand.Connection = $connection
$sqlCommand.CommandText = $sql

#execute script
Write-Output "start creating db..."
$sqlCommand.ExecuteReader()
Write-Output "finished creating db..."

$connection.Close()

#setup webservice
Write-Output "webservice setup:"

#create service for windows


$installDir = Read-Host -Prompt "directory to install the webserivice (default pwd)"

if($installDir -eq $null){
    $installDir = Get-Location
}

$webService = "UMWebService"

if ($IsWindows){
    $webService = "UMWebServiceWindows"
}

Copy-Item -Recurse -Force $webService $installDir

#setup applicaiton properties
$workingDirectory = Join-Path -Path $installDir -ChildPath $webService 
$propertiesFile = Join-Path -Path $workingDirectory -ChildPath "application.properties"
$configRaw = Get-Content -Path $propertiesFile | Out-String
$config = ConvertFrom-StringData($configRaw)

$config.'spring.datasource.url' = "jdbc:mysql:/$mysqlServer/:$mysqlPort/UserManagementProject/"

#unfortunately powershell provide no standart way to write the hashtable to a file, so i have enumarate over every key an write a custom output
$config.keys | Sort-Object | ForEach-Object{ Write-Output "$_=$($config.$_)" } | Out-File $propertiesFile