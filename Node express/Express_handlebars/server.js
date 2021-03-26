// *--------------------------------------------------------------------------------------------------------------------
// *Constants
// *--------------------------------------------------------------------------------------------------------------------
const express = require("express");
const app = express();
const handlebars = require("express-handlebars");
const util = require("util");
const bodyParser = require("body-parser");
const formidable = require("formidable");
const cookieParser = require("cookie-parser");
const sessionInit = require("express-session");
const fs = require("fs");
const mv = require("mv");

const quotes = require("./libs/quotesdata.js");
const authorsData = require("./libs/authorsdata.js");
const credentials = require("./credentials.js");

const dataDir = __dirname + "/data";
const photoDir = dataDir + "/photos";

// *--------------------------------------------------------------------------------------------------------------------
// *SETUP
// *--------------------------------------------------------------------------------------------------------------------
// Set the engine for handlebars
// OTHER OPTION
// app.engine("handlebars", handlebars({ defaultLayout: "main" }));
// Needed for sections
app.engine(
	"handlebars",
	handlebars({
		defaultLayout: "main",
		helpers: {
			section: function (name, options) {
				if (!this._sectionHelper) this._sectionHelper = {};
				this._sectionHelper[name] = options.fn(this);
				return null;
			},
		},
	})
);
app.set("view engine", "handlebars");

//  Setup for express
app.set("port", 3100);

//  Set static pages
app.use(express.static(__dirname + "/public"));

//  Partial views
app.use((req, res, next) => {
	res.locals.authors = authorsData.getAuthors();
	// console.log(util.inspect(authorsData.getAuthors()));     // Can be used to see what is inside the object
	next();
});

//  To work with forms
app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());

//  For the cookies
app.use(cookieParser(credentials.cookieSecret));

// For the sessions
app.use(
	sessionInit({
		secret: credentials.cookieSecret,
		resave: false,
		saveUninitialized: false,
	})
);

//	Check if the folder data / photo folder exist before creating them
if (!fs.existsSync(dataDir)) {
	fs.mkdirSync(dataDir);
}
if (!fs.existsSync(photoDir)) {
	fs.mkdirSync(photoDir);
}

// *--------------------------------------------------------------------------------------------------------------------
// *Routing
// *--------------------------------------------------------------------------------------------------------------------
// Default page
app.get("/", (req, res) => {
	// This adds some dynamic content to the home page
	q = quotes.random();
	res.render("home", { random_quote: q });
});

// About page
// Partials allow you to reuse components on different pages
app.get("/about", (req, res) => {
	res.render("about");
});

app.get("/section", (req, res) => {
	res.render("section", { layout: "sectionLayout" });
});

app.get("/newsletter", (req, res) => {
	//  Lets fill in the cookie in the Name field and the email in the Email field
	res.render("newsletter", {
		cookieName: req.signedCookies.name,
		sessionEmail: req.session.email,
	});
});

//  Procces the newsletter form
app.post("/formProcessing", (req, res) => {
	console.log("Name: " + req.body.name);
	console.log("Email: " + req.body.email);

	// We are gonna set a signed cookie!
	res.cookie("name", req.body.name, { signed: true });

	//  Save the session
	//  ! NOTE: it is req, not res
	req.session.email = req.body.email;

	res.redirect(303, "/thank-you");
});

//  Thank you page (redirect here after subscribing to the newsletter)
app.get("/thank-you", (req, res) => {
	res.render("thank-you");
});

//  Upload page
app.get("/upload", (req, res) => {
	const date = new Date();
	res.render("upload", { year: date.getFullYear(), month: date.getMonth() });
});

//  Handle the form on the upload page
app.post("/upload/:year/:month", (req, res) => {
	const form = new formidable.IncomingForm();

	form.parse(req, (err, fields, files) => {
		if (err) {
			return res.redirect(303, "/error");
		}
		console.log("received fields: " + util.inspect(fields));
		console.log("received files: " + util.inspect(files));

		//	Save the upload
		//	```````````````
		const photo = files.photo;
		//	Where to save the photo
		const dir = photoDir + "/" + Date.now(); //	Maakt een nieuwe folder aan om zo clashes te vermijden
		// Geeft de photo een nieuwe naam (zo hebben we zeker een jpg)
		// + zegt waar we deze zullen opslaan (in de nieuw gemaakte folder)
		const path = dir + "/" + "uploadedphoto.jpg";
		//	Create dir
		fs.mkdirSync(dir);
		//	Save it (actually, we move it from the temp folder)
		mv(photo.path.toString(), path.toString(), (err) => {
			if (err) {
				res.redirect(303, "/error");
			}
		});
		res.redirect(303, "/upload-succesful");
	});
});

//  Upload successful page (redirected here after uploading a file)
app.get("/upload-succesful", (req, res) => {
	res.render("upload-succesful");
});

// Error page
app.get("/error", (req, res) => {
	res.render("error");
});

// ! 404 page: Make sure this one is last, otherwise no other pages will ever load
app.use((req, res) => {
	res.status(404);
	res.render("404");
});

// 500 page, for internal errors
app.use((err, req, res) => {
	console.log(err);
	res.status(500);
	res.type("test/plain");
	res.send("500 - internal error");
});

// *--------------------------------------------------------------------------------------------------------------------
// *Server
// *--------------------------------------------------------------------------------------------------------------------

app.listen(app.get("port"), () => {
	console.log(`Server is running at http://localhost:${app.get("port")}`);
});
