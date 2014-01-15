// =============================================================================
//
// Copyright (c) 2009-2013 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================

var JSONRPCClient; ///< The core JSONRPC WebSocket client.

function addError(error)
{

}

function onWebSocketOpen(ws) 
{
    console.log("on open");
}

function onWebSocketMessage(evt) 
{
    console.log("on message:");
    constle.log(evt.data);
}

function onWebSocketClose()
{
    console.log("on close");
}

function onWebSocketError()
{
    console.log("on error");
}

function initializeButtons()
{
    $('#get-random-number').on('click', function() {
        var $this = $(this);
        JSONRPCClient.call("get-random-number", 
            null,
            function(result) {
                $('#random-number-get').html(result);
            },
            function(error) {
                addError(error);
            });
    });

    $('#set-random-number').on('click', function() {
        var $this = $(this);
        var random = Math.random() * 255;
        $('#random-number-set').html(random);
        JSONRPCClient.notify("set-random-number", random);
    });

    $('#enable-random-text-stream').on('switch-change', function(e, data) {
        var $this = $(this);
        JSONRPCClient.call("get-random-number", 
            data.value,
            function(result) {
                console.log(result);

                $('#random-number').html(result);
                $this.button('reset');
            },
            function(error) {
                alert("Failed callback.");
                $this.button('reset');
            });
        $this.button('loading');

        data.value


        var $element = $(data.el), value = data.value;
        console.log(e, $element, value);


    });


}

$(document).ready( function()
{
    // Initialize our JSONRPCClient
    JSONRPCClient = new $.JsonRpcClient(
        { 
            socketUrl: getWebSocketURL(), // get a websocket for the localhost
            onmessage: onWebSocketMessage,
            onopen: onWebSocketOpen,
            onclose: onWebSocketClose,
            onerror: onWebSocketError
        }
    );

    // Initialize all switches
    $('input[type="checkbox"],[type="radio"]').not('#create-switch').bootstrapSwitch();

    initializeButtons();

});
