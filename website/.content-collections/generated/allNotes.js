
export default [
  {
    "title": "Game Overview",
    "summary": "Overview of game points, scoring, strategies, and more",
    "week": 2,
    "content": "![Angled view of the override field showing the layout of the game. Outside two opposing sides of the field perimeter two are the alliance stations marked with matching colored lines. Inside the stations are a series of pins and cups. Inside the field perimeter is the arrangement of pins, cups, and goals.](https://content.vexrobotics.com/docs/2026-2027/override/online-manual/assets/image/Iso.png)  \nOverride field isometric, Game Manual V2.1: Section 2, released October 8, 2026, [vex.com](http://vex.com)\n\nFor the 2026-2027 the game we are playing is Override. Override is played on a 12’ x 12’ with 2 alliances, red and blue. The goal  of the game is to outscore the opposing team in a 2 minute match in which there is a 15 second autonomous period and a 1:45 driver control period. \n\nThe main way to score in this game is to stack cups and pins on goals, setting toggles to your alliances color and ending the match with your bot in the midfield.\n\nUnlike last years game, Pushback, this yeas game is not a cycling game. It is a game of strategy and stacking. To win you must be good at not only stacking pins but being able to keep track of time and be able to shut down opponents.\n\n12 points awarded to the team who wins in the autonomous period. If the autonomous period ends in a tie, 6 points are awared to both teams. There are multiple types of pins with color combinations being yellow-yellow, yellow-blue, yellow-red and red-blue with there being 19, 20, 20 and 4 of each colored pins respectively. Red and blue pins earn 5 points for their alliance respectively no matter where on the field they are. Yellow pins can earch up to 10 points depending on the color of the toggle in the quadrant where the yellow pin is placed. When the toggle color showing is yellow, the pins in that quadrant count for 0 points earned for both alliances. Each cup has a transparent and solid side. Which ever color shows through on the transparent side is the color which earns the points. At the end of the game",
    "_meta": {
      "filePath": "gameoverview.md",
      "fileName": "gameoverview.md",
      "directory": ".",
      "extension": "md",
      "path": "gameoverview"
    }
  },
  {
    "title": "Week 1 Overview",
    "summary": "Week 1 Overview",
    "week": 1,
    "content": "## First Design Ideas\n\n### Overview of Ideas for this week  \nThis week has been all about addressing parts or the robot and what functions the robot needs to be able to score. Main ways of scoring include stacking cups and pins onto coals, toggling and auton. To be able to do anything the bot needs some type of drive train. To stack cups, or bot must be able to reach large heights. For that we need some type of lift. Not only that but for toggles, the bot must be able to push the toggles and move them to the color wanted efficiently. To hold and collect pins from the dispenser, the bot must have some type of claw and some type of intake. We also have been finding out that we need to make a bulk part order of c-chanels and other parts to start building because we have none.\n\n### Lift Ideas \\+ Future Plans\n\nFor the lift we were deciding on creating either a double reverse 4 bar or a cascade 2 bar. \n\n|  | Pros | Cons |\n| :---- | :---- | :---- |\n| DR4B | 1\\. It would be really stable and wouldn’t shake much 2\\. We have experience making it 3\\. We have most of the pieces needed to build it 4\\. It wouldn’t take as much time to build  | 1\\. It is very heavy and would make our bot a lot slower 2\\. We would need a lot of c-chanels to achieve the same height as the cascade would 3\\. The only type of c-chanels we have are steel currently |\n| Cascade 2 Bar | 1\\. It is very lightweight 2\\. It is very reliable 3\\. It can become very compact helping with the height and width requirements 4\\. It has a wide range for picking up cups+pins | 1\\. None of us have built one before 2\\. We do not have matching c-chanels  3\\. It would take more time to build than the DR4B |\n\nIn the end we decided on building a Cascde 2 Bar but we haven’t started the building process yet.\n\n### Drivetrain Ideas \\+ Future Plans",
    "_meta": {
      "filePath": "week1.md",
      "fileName": "week1.md",
      "directory": ".",
      "extension": "md",
      "path": "week1"
    }
  },
  {
    "title": "Week 2 Overview",
    "summary": "Week 2 Overview",
    "week": 2,
    "content": "# Week 2\n## Lift type\nWe were going to create a cascade two bar but decided to create a reverse four bar instead because of lack of time and materials. We choose this because of the stability the 4 bar provides while lifting up the pin and the cup. The four bar is partially shaky currently because of lack of proper materials but it is functioning. The lengths of the c-channels do not align the way we would like them to but hopefully we can find better c-channels before the compitition. The next step is to attach the lift to the drivetrain.\n## Claw\nFor the claw we ordered the vex claw kit v2 but the kit would not have arrived in time. Because of this we had to design a replacment claw. By attaching two 5*5 c-channels side by side horizontally and attaching 8 steel screw we created somethng that can hold the pin and cup at the same time and when they are separated. We need to add mesh to the claw and attach it to the motor later. It also needs to be attach to the lift horizontal to the lift. \n## Drive-train\nThe drive trains basic design stayed the same but we decided to turn it into a gear train in order to link all of the wheels and have the bot moving at a constant pace. It also makes sure that the wheels are\n\n<iframe width=\"640\" height=\"480\" style=\"border:1px solid #eeeeee;\" src=\"https://3dviewer.net/embed.html#model=https://cdn.jsdelivr.net/gh/8995riptide/robot-code@latest/designs/dr4bp1-Assembly.step$camera=-277.24256,601.36328,640.06036,30.83373,190.59488,23.90777,0.00000,1.00000,0.00000,45.00000$projectionmode=perspective$envsettings=fishermans_bastion,off$backgroundcolor=255,255,255,255$defaultcolor=200,200,200$defaultlinecolor=100,100,100$edgesettings=off,0,0,0,1\"></iframe>",
    "_meta": {
      "filePath": "week2.md",
      "fileName": "week2.md",
      "directory": ".",
      "extension": "md",
      "path": "week2"
    }
  }
]