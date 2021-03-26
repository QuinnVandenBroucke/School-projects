const express = require("express");
const { hostname } = require("os");
const app = express();

app.set("port", 3100);

// Static files
app.use(express.static(__dirname + "/public"));
// Now it is possible to load: localhost:3100/cat.png

// Default page
app.get("/", (req, res) => {
	res.type("text/plain");
	res.send("Hallo world");
});

// About page
app.get("/about", (req, res) => {
	res.type("text/plain");
	res.send("Welcome to the about page");
});

// ! 404 page: Make sure this one is last, otherwise no other pages will ever load
app.use((req, res) => {
	res.type("text/plain");
	res.status(404);
	res.send("404 - page not found");
});

// 500 page, for internal errors
app.use((err, req, res) => {
	console.log(err);
	res.status(500);
	res.type("test/plain");
	res.send("500 - internal error");
});

// Setting up the server
app.listen(app.get("port"), () => {
	console.log(`Server is running at http://localhost:${app.get("port")}`);
});
