users = [
	{ name: "Quinn", location: "Belgium" },
	{ name: "Drake", location: "America" },
	{ name: "Sylke", location: "Belgium" },
];

exports.getUsers = () => {
	return users;
};

exports.getRandomUser = () => {
	return users[Math.floor(Math.random() * users.length)];
};
