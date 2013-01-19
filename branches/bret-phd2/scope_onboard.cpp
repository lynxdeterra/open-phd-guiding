/*
 *  scope_oncamera.h
 *  PHD Guiding
 *
 *  Created by Bret McKee
 *  Copyright (c) 2012 Bret McKee
 *  All rights reserved.
 *
 *  This source code is distributed under the following "BSD" license
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions are met:
 *    Redistributions of source code must retain the above copyright notice, 
 *     this list of conditions and the following disclaimer.
 *    Redistributions in binary form must reproduce the above copyright notice, 
 *     this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *    Neither the name of Bret McKee, Dad Dog Development,
 *     Craig Stark, Stark Labs nor the names of its 
 *     contributors may be used to endorse or promote products derived from 
 *     this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "phd.h"

ScopeOnCamera::ScopeOnCamera(void)
{
    m_Name =  "OnCamera";
}

bool ScopeOnCamera::Connect(void)
{
    bool bError = false;

    try
    {
        if (!pCamera || !pCamera->Connected)
        {
            throw ERROR_INFO("Attempt to Connect onboard when camera is not connected");
        }
        if (!pCamera->HasGuiderOutput)
        {
            throw ERROR_INFO("Attempt to Connect onboard when camera does not have guide output");
        }

        if (!IsConnected())
        {
            Scope::Connect();
        }
    }
    catch (...)
    {
        bError = true;
    }

    return bError;
}

bool ScopeOnCamera::Disconnect(void)
{
    bool bError = false;

    try
    {
        if (!IsConnected())
        {
            throw ERROR_INFO("Attempt to Disconnect onboard when not connected");
        }

        Scope::Disconnect();
    }
    catch (...)
    {
        bError = true;
    }

    return bError;
}

bool ScopeOnCamera::Guide(const GUIDE_DIRECTION direction, const int duration)
{
    bool bError = false;

    try
    {
        if (!IsConnected())
        {
            throw ERROR_INFO("Attempt to Guide while not connected");
        }
        pCamera->PulseGuideScope(direction,duration);
    }
    catch (...)
    {
        bError = true;
    }

    return bError;
}

bool ScopeOnCamera::HasNonGuiMove()
{
    return pCamera->HasNonGuiMove();
}

bool ScopeOnCamera::IsGuiding()
{
    return false;
}
