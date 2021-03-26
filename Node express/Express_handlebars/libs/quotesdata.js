const quotes = [{by: "Waldi Ravens", quote: "A C program is like a fast dance on a newly waxed dance floor by people carrying razors."},
                {by: "Keith Bostic", quote:"Perl – The only language that looks the same before and after RSA encryption."},
                {by: "Bjarne Stroustrup", quote: "In C++ it’s harder to shoot yourself in the foot, but when you do, you blow off your whole leg."},
                {by: "Robert Sewell", quote: "If Java had true garbage collection, most programs would delete themselves upon execution."},
                {by: "I Am Developer", quote: "CSS is easy, it's like riding a bike, which is on fire and the ground is on fire and everything is on fire because it is hell"}
                ];

exports.random = () => {
  return quotes[Math.floor(Math.random() * quotes.length)];
};
