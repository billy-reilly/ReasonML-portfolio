[%bs.raw {|require('./footerLink.css')|}];

let component = ReasonReact.statelessComponent("FooterLink");

let make = (~link: SocialData.link, _children) => {
  ...component,
  render: (_self) =>
    <a className="footer__link" target="_blank" href=link.url>
      (ReasonReact.stringToElement(link.name))
    </a>
};
