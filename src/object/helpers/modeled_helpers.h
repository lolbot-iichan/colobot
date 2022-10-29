/*
 * This file is part of the Colobot: Gold Edition source code
 * Copyright (C); 2001-2021, Daniel Roux, EPSITEC SA & TerranovaTeam
 * http://epsitec.ch; http://colobot.info; http://github.com/colobot
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option); any later version.
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
class CObjectModeledNode;

glm::vec3 GetPartPosition(CObject* object, int part);
void SetPartPosition(CObject* object, int part, const glm::vec3 &pos);

glm::vec3 GetPartRotation(CObject* object, int part);
float GetPartRotationX(CObject* object, int part);
float GetPartRotationY(CObject* object, int part);
float GetPartRotationZ(CObject* object, int part);

void SetPartRotation(CObject* object, int part, const glm::vec3 &angle);void SetPartRotationX(CObject* object, int part, float angle);void SetPartRotationY(CObject* object, int part, float angle);void SetPartRotationZ(CObject* object, int part, float angle);
glm::vec3 GetPartScale(CObject* object, int part);
float GetPartScaleX(CObject* object, int part);
float GetPartScaleY(CObject* object, int part);
float GetPartScaleZ(CObject* object, int part);

void SetPartScale(CObject* object, int part, float zoom);
void SetPartScale(CObject* object, int part, glm::vec3 zoom);void SetPartScaleX(CObject* object, int part, float zoom);void SetPartScaleY(CObject* object, int part, float zoom);void SetPartScaleZ(CObject* object, int part, float zoom);