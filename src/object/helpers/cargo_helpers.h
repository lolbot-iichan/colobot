/*
 * This file is part of the Colobot: Gold Edition source code
 * Copyright (C) 2001-2021, Daniel Roux, EPSITEC SA & TerranovaTeam
 * http://epsitec.ch; http://colobot.info; http://github.com/colobot
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see http://gnu.org/licenses
 */

#pragma once

class CObject;

bool IsObjectBeingTransported(CObject* object);
CObject* GetObjectTransporter(CObject* object);
// No SetObjectTransporter! Use SetObjectInSlot instead!

int  GetNumSlots(CObject *object);
bool HasCargoSlot(CObject *object);
bool HasPowerCellSlot(CObject *object);

CObject *GetObjectInSlot(CObject *object, int slotNum);
CObject *GetObjectInCargoSlot(CObject *object);
CObject *GetObjectInPowerCellSlot(CObject *object);

bool HasObjectInCargoSlot(CObject* object);
bool HasObjectInPowerCellSlot(CObject* object);

void SetObjectInSlot(CObject *object, int slotNum, CObject *cargo);
void SetObjectInCargoSlot(CObject *obj, CObject *cargo);
void SetObjectInPowerCellSlot(CObject *obj, CObject *cargo);
