//  --------------------------------------------------------------------------------------------------------------------
//  Constants
//  --------------------------------------------------------------------------------------------------------------------
const express = require("express");
const handlebars = require("express-handlebars");

const users = require("./libs/users.js");

//  --------------------------------------------------------------------------------------------------------------------
//  Setup
//  --------------------------------------------------------------------------------------------------------------------

//  Setup express
const app = express();

// Set the port
app.set("port", 3100);

// Define handlebars and sections
app.engine(
	"handlebars",
	handlebars({
		defaultLayout: "main",
		helpers: {
			section: function (name, options) {
				if (!this._sections) this._sections = {};
				this._sections[name] = options.fn(this);
				return null;
			},
		},
	})
);

//  Set the engine to handlebars
app.set("view engine", "handlebars");

//  Set the static folders
app.use(express.static(__dirname + "/public"));

//  --------------------------------------------------------------------------------------------------------------------
//  Routing
//  --------------------------------------------------------------------------------------------------------------------

// Home page
app.get("/", (req, res) => {
	res.render("home");
});

//  Ajax and javascript
app.get("/magic", (req, res) => {
	res.render("magic", { layout: "magicalLayout" });
});

//  AJAX response (in json format) for the magic page
app.get("/data/champ", (req, res) => {
	const user = users.getRandomUser();
	res.json(user);
});

// Some more ajax and javascript
app.get("/more", (req, res) => {
	res.render("more", { layout: "magicalLayout" });
});

//  Handle the more page
//  Javascript one
app.get("/ajax1", (req, res) => {
	res.type("text/plain");
	res.send("This was done with javascript!");
});
//  jQuery one
app.get("/ajax2", (req, res) => {
	res.type("text/plain");
	res.send("This was done with jQuery!");
});

//404 page
app.use((req, res) => {
	res.send("Error 404");
});

app.listen(app.get("port"), () => {
	console.log(`Server is running at http://localhost:${app.get("port")}`);
});
