|----------------------------------------------------------------------------|
| Warrior Functions
|----------------------------------------------------------------------------|
Sub WAR_Setup
 /if (${Me.Name.Equal[Lush]}) /log on
/return
|----------------------------------------------------------------------------|
SUB WAR_MacroSettings
/if (${Debug}) /echo |- WAR_MacroSettings ==>
	/call WriteToIni "${advSettings_Ini},WAR Functions,WAR Function#1" "check_Tanking" 1
	/call WriteToIni "${advSettings_Ini},WAR Functions,WAR Function#2" "check_Burns" 1
	/call WriteToIni "${advSettings_Ini},WAR Functions,WAR Function#3" "check_Buffs" 1
/if (${Debug}) /echo <== WAR_MacroSettings -|
/RETURN
|----------------------------------------------------------------------------|
SUB WAR_CharacterSettings
/RETURN
|----------------------------------------------------------------------------|
Sub WAR_Aliases
/return

| Checks the xtarget window for characters to buff with field armorer |
Sub check_FieldArmorer
	/declare i int local
	/declare currentTarget int local ${Target.ID}

	/for i 1 to ${Me.XTarget}			
		| continue if it's a pc and it's in range|
		/if (${Me.XTarget[${i}].Type.Equal[PC]} && ${Spawn[${Me.XTarget[${i}]}].Distance}<=60) {
			/call check_timer ${Me.XTarget[${i}]}FATimer
			/if (${Macro.Return}) { 
				/call cast_FA ${Target.ID}, ${Me.XTarget[${i}].ID}
			}
		}
	/next i
/return

| checks the timer on FA |
Sub check_timer(string timerName)
	/declare returnValue bool
	| create timer if it doesn't exist |
	/if (!${Defined[${timerName}]}) {
		/declare ${timerName} timer outer 40s
		/varset returnValue TRUE
	} else {
		| recast if < 1 second left on FA |
		/if (${${timerName}}<10) {
			/varset ${timerName} 40s
			/varset returnValue TRUE
		} else {
			/varset returnValue FALSE
		}
	}

/return ${returnValue}

| casts FA |
Sub cast_FA(int currentTarget, int FATarget)
	/call TrueTarget ${FATarget}
	/delay 1
	/doability "Field Armorer"
	/delay 1
	/call TrueTarget ${currentTarget}	
	| delay here so FA is ready the next loop. it's hacky but it's the only way i could get it to work |
	/delay 1s
/return

Sub WAR_Background_Events
	/call check_FieldArmorer
/return
