@echo off

for %%t in (test*.txt) do (
	echo Running %%~nt...
	..\src\Simplex.exe <%%t >%%~nt.out
	ren table.txt %%~nt.table > nul
	fc %%~nt.out %%~nt.out.correct > nul
	if errorlevel 1 (
	   echo failed [files %%~nt.out and %%~nt.out.correct differ]
	) else (
		fc %%~nt.table %%~nt.table.txt.correct > nul
		if errorlevel 1 (
		   echo failed [files %%~nt.table and %%~nt.table.txt.correct differ]
		) else echo passed
	)	
)

set errorlevel=0