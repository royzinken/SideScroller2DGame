// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

namespace EPlayerStates{
	enum State {
		idl,
		shooting
	};
}

namespace EItems {
	enum Powerup {
		eNone,
		eFirerate
	};
}

namespace EEnemyStates {
	enum State {
		eNone,
		eIDL,
		eAttacking,
		ePlayerDetected,
		eDead
	};
}