// Name: ODE
// ID: nishiowoOde
// Description: 3D physics using ODE.
// By: NishiOwO
// License: BSD-3-Clause

// Repository is at https://github.com/nishiowo/tw-ode

(async function (Scratch) {
	"use strict";

	if (!Scratch.extensions.unsandboxed) {
		throw new Error("ODE must be run unsandboxed");
	}

	let Module, dInitODE2, dCloseODE, dWorldStep, dWorldCreate, dHashSpaceCreate;
	let ode;
	let embedded = false;
	var ODEWASM;
	let w_to_s = {}; /* world to space */

	/* DO NOT REMOVE THE COMMENT BELOW!!! */
	/* EMBED ODEJS.JS HERE */

	if (embedded) {
		ode = ODEWASM;
	} else {
		ode = await Scratch.external.evalAndReturn(
			"",
			"ODEWASM"
		);
	}

	Module = await ode();
	dInitODE2 = Module.cwrap("dInitODE2", "number", ["number"]);
	dCloseODE = Module.cwrap("dCloseODE", null, []);
	dWorldStep = Module.cwrap("dWorldStep", null, ["number", "number"]);
	dWorldCreate = Module.cwrap("dWorldCreate", "number", []);
	dHashSpaceCreate = Module.cwrap("dHashSpaceCreate", "number", ["number"]);

	const blockIconURI = "data:image/png;base64,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";

	class ODE {
		getInfo() {
			return {
				id: "nishiowoOde",
				name: Scratch.translate("ODE"),
				blockIconURI: blockIconURI,
				color1: "#444444",
				blocks: [
					{
						opcode: "resetAll",
						blockType: Scratch.BlockType.COMMAND,
						text: Scratch.translate(
							"reset all"
						)
					},
					{
						opcode: "createWorld",
						blockType: Scratch.BlockType.REPORTER,
						text: Scratch.translate(
							"create world and space
						)
					}
				]
			};
		}

		resetAll() {
			for(let i in w_to_s);

			dCloseODE();
			dInitODE2(0);
		}

		createWorld() {
			let world = d
		}
	};

	dInitODE2(0);

	Scratch.extensions.register(new ODE());
})(Scratch);
